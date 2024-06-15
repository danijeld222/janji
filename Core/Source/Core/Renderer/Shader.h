#pragma once

#include "Core/Defines.h"

#include <string>
#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace Core 
{
	class Shader
	{
	public:
		static Ref<Shader> Create(const std::string& name, const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexFilepath, const std::string& fragmentFilepath);
		static Ref<Shader> CreateWithSource(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		
		~Shader();
		
		void Bind() const;
		void Unbind() const;
		
		const std::string& GetName() const;
		
		void UploadUniformInt(const std::string& name, int value);
		
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
		
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		
		// NOTE: Dani - This should be private or protected so we can not call constructor directly
		//				Take a look at this https://stackoverflow.com/questions/8147027/how-do-i-call-stdmake-shared-on-a-class-with-only-protected-or-private-const/8147213#8147213
		//				Idea is that we dont want to create instance without it being shared_ptr
	public:
		Shader(const std::string& name, const std::string& filepath);
		Shader(const std::string& name, const std::string& vertexFilepath, const std::string& fragmentFilepath, b8 _);
		Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	
	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	
	private:
		u32 m_RendererID;
		std::string m_Name;
	};
	
	class ShaderLibrary
	{
	public:
		void Add(const Ref<Shader>& shader);
		
		Ref<Shader> Load(const std::string& name, const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& vertexFilepath, const std::string& fragmentFilepath);
		Ref<Shader> Get(const std::string& name);
		
		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}