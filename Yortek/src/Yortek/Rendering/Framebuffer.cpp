#include "Yortek/Rendering/Framebuffer.h"
#include "Yortek/Core/Environment.h"
#include "Yortek/Debug/Log.h"
#include "Platform/OpenGL/OGL_Framebuffer.h"

namespace Yortek::Rendering
{
	Shared<Framebuffer> Framebuffer::Builder::build() const
	{
		switch (Environment::get_graphics_api())
		{
		case GraphicsAPI::None: return nullptr;
		case GraphicsAPI::OpenGL: return CreateShared<OGL::OGL_Framebuffer>(*this);
		}

		Debug::Log::error("Invalid GraphcisAPI");
		return nullptr;
	}
}