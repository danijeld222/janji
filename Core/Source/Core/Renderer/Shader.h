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
		Shader(const std::string& filepath);
		// NOTE: Dani - added bool so we don't have two construction with indentical signature: look at this https://isocpp.org/wiki/faq/ctors#named-ctor-idiom
		Shader(const std::string& vertexFilepath, const std::string& fragmentFilepath, b8 findByPath);
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();
		
		void Bind() const;
		void Unbind() const;
		
		void UploadUniformInt(const std::string& name, int value);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
		
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		
	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	
	private:
		u32 m_RendererID;
	};
}