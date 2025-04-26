#include "Renderer.h"

#include "Core/Debug/Instrumentor.h"

#include <glm/gtc/matrix_transform.hpp>
#include <array>

namespace Core
{
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;
	
	void Renderer::Init()
	{
		CORE_PROFILE_FUNCTION();
		
		RendererCommands::Init();
		Renderer2D::Init();
	}
	
	void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
	}
	
	void Renderer::OnWindowResize(u32 width, u32 height)
	{
		RendererCommands::SetViewport(0, 0, width, height);
	}
	
	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	
	void Renderer::EndScene()
	{
	}
	
	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);
		
		vertexArray->Bind();
		RendererCommands::DrawIndexed(vertexArray);
	}
	
	// Renderer 2D
	
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		f32 TexIndex;
		f32 TilingFactor;
	};
	
	struct Renderer2DData
	{
		static const u32 MaxQuads = 20000;
		static const u32 MaxVertices = MaxQuads * 4;
		static const u32 MaxIndices = MaxQuads * 6;
		static const u32 MaxTextureSlots = 32;
		
		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
		
		u32 QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;
		
		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		u32 TextureSlotIndex = 1; // 0 = white texture
		
		glm::vec4 QuadVertexPositions[4];
		
		Renderer2D::Statistics Stats;
	};
	
	static Renderer2DData s_Data;
	
	void Renderer2D::Init()
	{
		CORE_PROFILE_FUNCTION();
		
		s_Data.QuadVertexArray = VertexArray::Create();
		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float, "a_TexIndex" },
			{ ShaderDataType::Float, "a_TilingFactor" }
		});
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);
		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];
		
		u32* quadIndices = new u32[s_Data.MaxIndices];
		
		u32 offset = 0;
		for (u32 i = 0; i < s_Data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;
			
			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;
			
			offset += 4;
		}
		
		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;
		
		s_Data.WhiteTexture.reset(new Texture2D(1, 1));
		u32 whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(u32));
		
		i32 samplers[s_Data.MaxTextureSlots];
		for (u32 i = 0; i < s_Data.MaxTextureSlots; i++)
		{
			samplers[i] = i;
		}
		
		s_Data.TextureShader = Shader::Create("TextureShader", "Assets/Shaders/Texture.glsl");
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetIntArray("u_Textures", samplers, s_Data.MaxTextureSlots);
		
		// Set all texture slots to 0
		s_Data.TextureSlots[0] = s_Data.WhiteTexture;
		
		s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}
	
	void Renderer2D::Shutdown()
	{
		CORE_PROFILE_FUNCTION();
		
		delete[] s_Data.QuadVertexBufferBase;
	}
	
	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		CORE_PROFILE_FUNCTION();
		
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		
		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
		
		s_Data.TextureSlotIndex = 1;
	}
	
	void Renderer2D::EndScene()
	{
		CORE_PROFILE_FUNCTION();
		
		u32 dataSize = (u32)((u8*)s_Data.QuadVertexBufferPtr - (u8*)s_Data.QuadVertexBufferBase);
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);
		
		Flush();
	}
	
	void Renderer2D::Flush()
	{
		if (s_Data.QuadIndexCount == 0)
		{
			return;
		}
		
		for (u32 i = 0; i < s_Data.TextureSlotIndex; i++)
		{
			s_Data.TextureSlots[i]->Bind(i);
		}
		
		RendererCommands::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
		s_Data.Stats.DrawCalls++;
	}
	
	void Renderer2D::FlushAndReset()
	{
		EndScene();
		
		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
		
		s_Data.TextureSlotIndex = 1;
	}
	
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({position.x, position.y, 0.0f }, size, color);
	}
	
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		CORE_PROFILE_FUNCTION();
		
		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
		{
			FlushAndReset();
		}
		
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		
		constexpr size_t quadVertexCount = 4;
		const f32 textureIndex = 0.0f;
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		const f32 tilingFactor = 1.0f;
		
		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;
		s_Data.Stats.QuadCount++;
	}
	
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, f32 tilingFactor, const glm::vec4& tintColor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
	}
	
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, f32 tilingFactor, const glm::vec4& tintColor)
	{
		CORE_PROFILE_FUNCTION();
		
		constexpr size_t quadVertexCount = 4;
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		
		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
		{
			FlushAndReset();
		}
		
		f32 textureIndex = 0.0f;
		for (u32 i = 1; i < s_Data.TextureSlotIndex; i++)
		{
			if (*s_Data.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (f32)i;
				break;
			}
		}
		
		if (textureIndex == 0.0f)
		{
			if (s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
			{
				FlushAndReset();
			}
			
			textureIndex = (f32)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}
		
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		
		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = tintColor;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr++;
		}
		
		s_Data.QuadIndexCount += 6;
		s_Data.Stats.QuadCount++;
	}
	
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec2& spriteIndex, f32 tilingFactor, const glm::vec4& tintColor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, spriteIndex, tilingFactor, tintColor);
	}
	
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec2& spriteIndex, f32 tilingFactor, const glm::vec4& tintColor)
	{
		CORE_PROFILE_FUNCTION();

		constexpr f32 sheetWidth = 1536.0f;
		constexpr f32 sheetHeight = 2304.0f;
		constexpr f32 spriteWidth = 48.0f;
		constexpr f32 spriteHeight = 48.0f;

		constexpr size_t quadVertexCount = 4;
		//constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		glm::vec2 textureCoords[] = {
			{ (spriteIndex.x * spriteWidth) / sheetWidth, (spriteIndex.y * spriteHeight) / sheetHeight },
			{ ((spriteIndex.x + 1) * spriteWidth) / sheetWidth, (spriteIndex.y * spriteHeight) / sheetHeight },
			{ ((spriteIndex.x + 1) * spriteWidth) / sheetWidth, ((spriteIndex.y + 1) * spriteHeight) / sheetHeight },
			{ (spriteIndex.x * spriteWidth) / sheetWidth, ((spriteIndex.y + 1) * spriteHeight) / sheetHeight }
		};

		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
		{
			FlushAndReset();
		}

		f32 textureIndex = 0.0f;
		for (u32 i = 1; i < s_Data.TextureSlotIndex; i++)
		{
			if (*s_Data.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (f32)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			if (s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
			{
				FlushAndReset();
			}
			
			textureIndex = (f32)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = tintColor;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;
		s_Data.Stats.QuadCount++;
	}
	
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, f32 rotation, const glm::vec4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}
	
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, f32 rotation, const glm::vec4& color)
	{
		CORE_PROFILE_FUNCTION();
		
		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
		{
			FlushAndReset();
		}
		
		constexpr size_t quadVertexCount = 4;
		const f32 textureIndex = 0.0f;
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		const f32 tilingFactor = 1.0f;
		
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), {0.0f, 0.0f, 1.0f})
			* glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		
		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr++;
		}
		
		s_Data.QuadIndexCount += 6;
		s_Data.Stats.QuadCount++;
	}
	
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, f32 rotation, const Ref<Texture2D>& texture, f32 tilingFactor, const glm::vec4& tintColor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
	}
	
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, f32 rotation, const Ref<Texture2D>& texture, f32 tilingFactor, const glm::vec4& tintColor)
	{
		CORE_PROFILE_FUNCTION();
		
		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
		{
			FlushAndReset();
		}
		
		constexpr size_t quadVertexCount = 4;
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		
		f32 textureIndex = 0.0f;
		for (u32 i = 1; i < s_Data.TextureSlotIndex; i++)
		{
			if (*s_Data.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (f32)i;
				break;
			}
		}
		
		if (textureIndex == 0.0f)
		{
			if (s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
			{
				FlushAndReset();
			}
			
			textureIndex = (f32)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}
		
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), {0.0f, 0.0f, 1.0f})
			* glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		
		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = tintColor;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr++;
		}
		
		s_Data.QuadIndexCount += 6;
		s_Data.Stats.QuadCount++;
	}
	
	void Renderer2D::ResetStats()
	{
		memset(&s_Data.Stats, 0, sizeof(Statistics));
	}
	
	Renderer2D::Statistics Renderer2D::GetStats()
	{
		return s_Data.Stats;
	}
}