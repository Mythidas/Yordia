#pragma once

#include "Yortek/Core/Defines.h"
#include "Yortek/Tools/BuilderHelper.h"

namespace Yortek::Rendering
{
	enum class BufferUsage
	{
		Vertex,
		Index,
		Uniform,
		ShaderStorage
	};

	enum class BufferRate
	{
		Static,
		Dynamic
	};

	enum class BufferAccess
	{
		ReadOnly,
		WriteOnly,
		ReadWrite
	};

	class RenderBuffer
	{
	public:
		struct Builder : Tools::BuilderHelper<Builder>
		{
			size_t size;
			uint32_t binding;
			BufferUsage usage;
			BufferRate rate;

			Builder& set_size(size_t _size) { return _set_prop(size, _size); }
			Builder& set_binding(uint32_t _binding) { return _set_prop(binding, _binding); }
			Builder& set_usage(BufferUsage _usage) { return _set_prop(usage, _usage); }
			Builder& set_rate(BufferRate _rate) { return _set_prop(rate, _rate); }
			Shared<RenderBuffer> build() const;
		};

		virtual void bind() const = 0;
		virtual void set_data(void* data, size_t size, uint32_t offset) = 0;
		virtual void* map_buffer_ptr(BufferAccess access) = 0;
		virtual void unmap_buffer_ptr() = 0;
	};
}