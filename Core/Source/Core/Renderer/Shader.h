#pragma once

#include "Core/Defines.h"

#include <string>
#include <glm/glm.hpp>

namespace Core 
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();
		
		void Bind() const;
		void Unbind() const;
		
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		
	private:
		u32 m_RendererID;
	};
}