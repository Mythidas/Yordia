#pragma once

#include "Yortek/Core/Defines.h"
#include "Yortek/Math/include.h"
#include "Yortek/Tools/BuilderHelper.h"
#include "Yortek/Tools/Path.h"

namespace Yortek::Rendering
{
	using namespace Math;

	enum class ImageType
	{
		e1D,
		e2D,
		e3D
	};

	enum class ImageFormat
	{
		R8,
		RGBA8,
		RGBA32F
	};

	enum class ImageWrap
	{
		Repeat,
		ClampToEdge,
		MirroredRepeat
	};

	enum class ImageTiling
	{
		Linear,
		Nearest
	};

	class Image
	{
	public:
		struct Builder : Tools::BuilderHelper<Builder>
		{
			uint32_t binding{ 0 };
			ImageType type{ ImageType::e2D };
			ImageFormat format{ ImageFormat::RGBA8 };
			ImageWrap wrap{ ImageWrap::Repeat };
			ImageTiling tiling{ ImageTiling::Nearest };
			IVector3 size{ 1, 1, 1 };
			bool flipped{ false };

			Builder& set_binding(uint32_t _binding) { return _set_prop(binding, _binding); }
			Builder& set_type(ImageType _type) { return _set_prop(type, _type); }
			Builder& set_format(ImageFormat _format) { return _set_prop(format, _format); }
			Builder& set_wrap(ImageWrap _wrap) { return _set_prop(wrap, _wrap); }
			Builder& set_tiling(ImageTiling _tiling) { return _set_prop(tiling, _tiling); }
			Builder& set_size(const IVector3& _size) { return _set_prop(size, _size); }
			Builder& set_flipped(bool _flipped) { return _set_prop(flipped, _flipped); }
			Shared<Image> build() const;
		};

		virtual void bind(uint32_t slot) const = 0;
		virtual void set_data(void* data, size_t size) = 0;
		virtual void load_data(const Tools::Path& path) = 0;

		virtual IVector3 get_size() const = 0;
		virtual void* get_render_id() const = 0;
	};
}