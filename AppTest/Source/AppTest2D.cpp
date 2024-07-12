#include "AppTest2D.h"
#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

AppTest2D::AppTest2D()
	: Layer("AppTest2D"), m_CameraController(1280.0f / 720.0f)
{
}

void AppTest2D::OnAttach()
{
	m_SquareVA = Core::VertexArray::Create();
	
	f32 squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};
	
	Core::Ref<Core::VertexBuffer> squareVB;
	squareVB.reset(new Core::VertexBuffer(squareVertices, sizeof(squareVertices)));
	squareVB->SetLayout({
		{ Core::ShaderDataType::Float3, "a_Position" }
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	u32 squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Core::Ref<Core::IndexBuffer> squareIB;
	squareIB.reset(new Core::IndexBuffer(squareIndices, sizeof(squareIndices) / sizeof(u32)));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = Core::Shader::Create("FlatColorShader", "Assets/Shaders/FlatColor.glsl");
}

void AppTest2D::OnDetach()
{
}

void AppTest2D::OnUpdate(Core::Timestep timestep)
{
	m_CameraController.OnUpdate(timestep);

	Core::RendererCommands::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Core::RendererCommands::Clear();
	
	Core::Renderer::BeginScene(m_CameraController.GetCamera());
	
	m_FlatColorShader->Bind();
	m_FlatColorShader->UploadUniformFloat4("u_Color", m_SolidColor);

	Core::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Core::Renderer::EndScene();
}

void AppTest2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SolidColor));
	ImGui::End();
}

void AppTest2D::OnEvent(Core::Event& event)
{
	m_CameraController.OnEvent(event);
}