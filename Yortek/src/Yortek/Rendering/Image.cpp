#include "Yortek/Rendering/Image.h"
#include "Yortek/Core/Application.h"
#include "Platform/OpenGL/OGL_Image.h"

namespace Yortek::Rendering
{
	Shared<Image> Image::Builder::build() const
	{
		switch (Application::get_backend())
		{
		case ApplicationBackend::None: return nullptr;
		case ApplicationBackend::OpenGL: return CreateShared<OGL::OGL_Image>(*this);
		}

		return nullptr;
	}
}