#include "Shader.h"

#include "Core/Logger/Logger.h"
#include "Core/Asserts.h"

#include <vector>

#include "glad/gl.h"
#include <glm/gtc/type_ptr.hpp>

namespace Core
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
		{
			return GL_VERTEX_SHADER;
		}
		if (type == "fragment" || type == "pixel")
		{
			return GL_FRAGMENT_SHADER;
		}
		
		COREASSERT_MESSAGE(false, "Unknown type");
		return 0;
	}
	
	Shader::Shader(const std::string& filepath)
	{
		std::string source = ReadFile(filepath);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);
	}
	
	Shader::Shader(const std::string& vertexFilepath, const std::string& fragmentFilepath, b8 findByPath)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = ReadFile(vertexFilepath);
		sources[GL_FRAGMENT_SHADER] = ReadFile(fragmentFilepath);
		Compile(sources);
	}
	
	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
	}
	
	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}
	
	std::string Shader::ReadFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in, std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			char result[200];
			const char* one = "Could not open file ";
			strcpy(result, one);
			strcat(result, filepath.c_str());
			COREASSERT_MESSAGE(false, result);
		}
		
		return result;
	}
	
	std::unordered_map<GLenum, std::string> Shader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			COREASSERT_MESSAGE((eol != std::string::npos), "Syntax error");
			
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			COREASSERT_MESSAGE(ShaderTypeFromString(type), "Invalid shader type specified");
			
			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}
		
		return shaderSources;
	}
	
	void Shader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		GLuint program = glCreateProgram();
		std::vector<GLenum> glShaderIDs(shaderSources.size());
		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;
			
			GLuint shader = glCreateShader(type);
			
			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);
			
			glCompileShader(shader);
			
			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
				
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
				
				glDeleteShader(shader);
				
				COREERROR("{0}", (char*)infoLog.data());
				COREASSERT_MESSAGE(false, "Fragment shader compilation failure!");
				break;
			}
			
			glAttachShader(program, shader);
			glShaderIDs.push_back(shader);
		}
		
		m_RendererID = program;
		
		// Link our program
		glLinkProgram(program);
		
		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
			
			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
			
			// We don't need the program anymore.
			glDeleteProgram(program);
			
			for (auto id : glShaderIDs)
			{
				glDeleteShader(id);
			}
			
			COREERROR("{0}", (char*)infoLog.data());
			COREASSERT_MESSAGE(false, "Shader link failure!");
			return;
		}
		
		for (auto id : glShaderIDs)
		{
			glDetachShader(program, id);
		}
	}
	
	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}
	
	void Shader::Unbind() const
	{
		glUseProgram(0);
	}
	
	void Shader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}
	
	void Shader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}
	
	void Shader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}
	
	void Shader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}
	
	void Shader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}
	
	void Shader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	
	void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}