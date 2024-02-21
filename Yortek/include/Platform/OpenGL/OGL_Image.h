#pragma once

#include "Yortek/Rendering/Image.h"

namespace Yortek::Rendering::OGL
{
	class OGL_Image : public Image
	{
	public:
		OGL_Image(const Builder& builder);

		virtual void bind(uint32_t slot) const override;
		virtual void set_data(void* data, size_t size) override;
		virtual void load_data(const Tools::Path& path) override;

		virtual Math::IVector3 get_size() const override { return m_builder.size; };
		virtual void* get_render_id() const override;

	private:
		Builder m_builder;
		uint32_t m_render_id;
	};
}