#pragma once

#include "Yortek/Rendering/Framebuffer.h"

namespace Yortek::Rendering::OGL
{
	class OGL_Framebuffer : public Framebuffer
	{
	public:
		OGL_Framebuffer(const Builder& builder);
		~OGL_Framebuffer();

		virtual void bind() const override;
		virtual void unbind() const override;
		virtual void resize(const Math::IVector2& size) override;

		virtual Math::IVector2 get_size() const override { return m_size; }
		virtual void* get_render_id() const override { return reinterpret_cast<void*>((uint32_t)m_texture); }

	private:
		uint32_t m_renderID{ 0 };
		uint32_t m_texture{ 0 };
		uint32_t m_render_object{ 0 };
		glm::uvec2 m_size;
	};
}