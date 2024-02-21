#include "Platform/OpenGL/OGL_Shader.h"
#include "Yortek/Tools/Path.h"

#include <glad/glad.h>

namespace Yortek::Rendering::OGL
{
	namespace Utils
	{
		bool LogShaderError(uint32_t shader)
		{
			int success;
			char infoLog[512];

			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 512, nullptr, infoLog);
				// Debug::Log::Error("Shader Compile Error: {0}", infoLog);
				return false;
			}

			return true;
		}

		bool LogProgramError(uint32_t program)
		{
			int success;
			char infoLog[512];

			glGetProgramiv(program, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(program, 512, nullptr, infoLog);
				// Debug::Log::Error("Program Link Error: {0}", infoLog);
				return false;
			}

			return true;
		}

		int GetAttributeSize(VertexAttribute attrib)
		{
			switch (attrib)
			{
			case VertexAttribute::Float: return 4 * 1;
			case VertexAttribute::Float2: return 4 * 2;
			case VertexAttribute::Float3: return 4 * 3;
			case VertexAttribute::Float4: return 4 * 4;
			default: return 4;
			}
		}

		int GetAttributeCount(VertexAttribute attrib)
		{
			switch (attrib)
			{
			case VertexAttribute::Float: return 1;
			case VertexAttribute::Float2: return 2;
			case VertexAttribute::Float3: return 3;
			case VertexAttribute::Float4: return 4;
			default: return 1;
			}
		}

		GLenum GetAttributeType(VertexAttribute attrib)
		{
			switch (attrib)
			{
			case VertexAttribute::Float: return GL_FLOAT;
			case VertexAttribute::Float2: return GL_FLOAT;
			case VertexAttribute::Float3: return GL_FLOAT;
			case VertexAttribute::Float4: return GL_FLOAT;
			default: return GL_FLOAT;
			}
		}
	}

	OGL_Shader::OGL_Shader(const Builder& builder)
		: m_builder(builder), m_render_id(0), m_vertex_id(0)
	{
		std::string vertSrc = Tools::Path(builder.vert_path).read_to_string();
		std::string fragSrc = Tools::Path(builder.frag_path).read_to_string();

		const char* vertCode = vertSrc.c_str();
		const char* fragCode = fragSrc.c_str();

		uint32_t vertShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertShader, 1, &vertCode, nullptr);
		glCompileShader(vertShader);

		if (!Utils::LogShaderError(vertShader))
		{
			// Debug::Log::Error("Failed to Create Shader: {0}", builder.VertPath);
			return;
		}

		uint32_t fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fragCode, nullptr);
		glCompileShader(fragShader);

		if (!Utils::LogShaderError(fragShader))
		{
			// Debug::Log::Error("Failed to Create Shader: {0}", builder.FragPath);
			return;
		}

		m_render_id = glCreateProgram();
		glAttachShader(m_render_id, vertShader);
		glAttachShader(m_render_id, fragShader);
		glLinkProgram(m_render_id);

		if (!Utils::LogProgramError(m_render_id))
		{
			// Debug::Log::Error("Failed to Create Program ID {0}: Link Error", m_RenderID);
			return;
		}

		glDeleteShader(vertShader);
		glDeleteShader(fragShader);

		glGenVertexArrays(1, &m_vertex_id);
		glBindVertexArray(m_vertex_id);

		m_builder.p_vertex_buffer->bind();
		m_builder.p_index_buffer->bind();

		GLsizei stride = 0;
		for (auto& attrib : m_builder.attributes)
		{
			stride += Utils::GetAttributeSize(attrib);
		}

		size_t offset = 0;
		for (GLuint i = 0; i < m_builder.attributes.size(); i++)
		{
			glEnableVertexArrayAttrib(m_vertex_id, i);
			glVertexAttribPointer(i, Utils::GetAttributeCount(m_builder.attributes[i]), Utils::GetAttributeType(m_builder.attributes[i]), GL_FALSE, stride, (void*)offset);
			offset += Utils::GetAttributeSize(m_builder.attributes[i]);
		}

		uint32_t camera_index = glGetUniformBlockIndex(m_render_id, "Camera");
		glUniformBlockBinding(m_render_id, camera_index, 0);
	}

	void OGL_Shader::draw(uint32_t count) const
	{
		if (count == 0) return;

		glUseProgram(m_render_id);
		glBindVertexArray(m_vertex_id);

		for (auto& buffer : m_builder.p_render_buffers)
		{
			buffer->bind();
		}

		if (m_builder.p_index_buffer)
		{
			m_builder.p_index_buffer->bind();
			glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, count);
		}
	}
}