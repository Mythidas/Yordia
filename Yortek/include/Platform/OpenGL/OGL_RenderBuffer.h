#pragma once

#include "Yortek/Rendering/RenderBuffer.h"

namespace Yortek::Rendering::OGL
{
	class OGL_RenderBuffer : public RenderBuffer
	{
	public:
		OGL_RenderBuffer(const Builder& builder);

		virtual void bind() const override;
		virtual void set_data(void* data, size_t size, uint32_t offset) override;
		virtual void* map_buffer_ptr(BufferAccess access) override;
		virtual void unmap_buffer_ptr() override;

	private:
		Builder m_builder;
		uint32_t m_render_id;
	};
}