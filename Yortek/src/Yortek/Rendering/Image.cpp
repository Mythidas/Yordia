#include "YTEngine/Graphics/Image.h"
#include "YTEngine/Core/Application.h"
#include "Platform/OpenGL/OGL_Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Yor
{
	Shared<Image> Image::Builder::build() const
	{
		switch (Application::getBackend())
		{
		case ApplicationBackend::None: return nullptr;
		case ApplicationBackend::OpenGL: return CreateShared<OGL::OGL_Image>(*this);
		}

		return nullptr;
	}
}