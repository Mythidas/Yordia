#pragma once

#include "Yortek/Core/Defines.h"
#include "Yortek/Tools/BuilderHelper.h"
#include "Yortek/Rendering/RenderBuffer.h"
#include "Yortek/Tools/Path.h"

namespace Yortek::Rendering
{
	enum class VertexAttribute
	{
		Float,
		Float2,
		Float3,
		Float4
	};

	class Shader
	{
	public:
		struct Builder : Tools::BuilderHelper<Builder>
		{
			Tools::Path vert_path;
			Tools::Path frag_path;
			Shared<RenderBuffer> p_vertex_buffer;
			Shared<RenderBuffer> p_index_buffer;
			std::vector<Shared<RenderBuffer>> p_render_buffers;
			std::vector<VertexAttribute> attributes;

			Builder& set_vert_path(const Tools::Path& _path) { return _set_prop(vert_path, _path); }
			Builder& set_frag_path(const Tools::Path& _path) { return _set_prop(frag_path, _path); }
			Builder& set_vertex_buffer(const Shared<RenderBuffer>& _buffer) { return _set_prop(p_vertex_buffer, _buffer); }
			Builder& set_index_buffer(const Shared<RenderBuffer>& _buffer) { return _set_prop(p_index_buffer, _buffer); }
			Builder& set_render_buffers(const std::vector<Shared<RenderBuffer>>& _buffers) { return _set_prop(p_render_buffers, _buffers); }
			Builder& set_attributes(const std::vector<VertexAttribute>& _attributes) { return _set_prop(attributes, _attributes); }
			Shared<Shader> build() const;
		};

		virtual void draw(uint32_t count) const = 0;
	};
}