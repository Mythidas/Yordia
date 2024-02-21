#include "Yortek/Rendering/Image.h"
#include "Yortek/Core/Environment.h"
#include "Yortek/Debug/Log.h"
#include "Platform/OpenGL/OGL_Image.h"

namespace Yortek::Rendering
{
	Shared<Image> Image::Builder::build() const
	{
		switch (Environment::get_graphics_api())
		{
		case GraphicsAPI::None: return nullptr;
		case GraphicsAPI::OpenGL: return CreateShared<OGL::OGL_Image>(*this);
		}

		Debug::Log::error("Invalid GraphicsAPI");
		return nullptr;
	}
}