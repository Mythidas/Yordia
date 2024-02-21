#pragma once

#include "Yortek/Rendering/Shader.h"

namespace Yortek::Rendering::OGL
{
	class OGL_Shader : public Shader
	{
	public:
		OGL_Shader(const Builder& builder);

		virtual void draw(uint32_t count) const override;

	private:
		Builder m_builder;
		uint32_t m_render_id;
		uint32_t m_vertex_id;
	};
}