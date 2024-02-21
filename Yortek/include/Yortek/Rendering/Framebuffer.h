#pragma once

#include "Yortek/Core/Defines.h"
#include "Yortek/Math/include.h"
#include "Yortek/Tools/BuilderHelper.h"

namespace Yortek::Rendering
{
	class Framebuffer
	{
	public:
		struct Builder : Tools::BuilderHelper<Builder>
		{
			Math::IVector2 size;

			Builder& set_size(const Math::IVector2& _size) { return _set_prop(size, _size); }
			Shared<Framebuffer> build() const;
		};


		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual void resize(const Math::IVector2& size) = 0;
		virtual Math::IVector2 get_size() const = 0;
		virtual void* get_render_id() const = 0;
	};
}