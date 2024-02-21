#include "Platform/OpenGL/OGL_Framebuffer.h"
#include "Yortek/Debug/Log.h"

#include <glad/glad.h>

namespace Yortek::Rendering::OGL
{
	OGL_Framebuffer::OGL_Framebuffer(const Builder& builder)
	{
		resize(builder.size);
	}

	OGL_Framebuffer::~OGL_Framebuffer()
	{
		glDeleteFramebuffers(1, &m_renderID);
		glDeleteTextures(1, &m_texture);
		glDeleteRenderbuffers(1, &m_render_object);
	}

	void OGL_Framebuffer::bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_renderID);
	}

	void OGL_Framebuffer::unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OGL_Framebuffer::resize(const Math::IVector2& size)
	{
		if (size.x <= 0 || size.y <= 0) return;
		m_size = size;

		glDeleteFramebuffers(1, &m_renderID);
		glDeleteTextures(1, &m_texture);
		glDeleteRenderbuffers(1, &m_render_object);

		glGenFramebuffers(1, &m_renderID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_renderID);

		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

		glGenRenderbuffers(1, &m_render_object);
		glBindRenderbuffer(GL_RENDERBUFFER, m_render_object);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_render_object);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			Debug::Log::error("Framebuffer failed to create!");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}