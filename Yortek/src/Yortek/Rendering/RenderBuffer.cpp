#include "Yortek/Rendering/RenderBuffer.h"
#include "Yortek/Core/Environment.h"
#include "Yortek/Debug/Log.h"
#include "Platform/OpenGL/OGL_RenderBuffer.h"

namespace Yortek::Rendering
{
	Shared<RenderBuffer> RenderBuffer::Builder::build() const
	{
		switch (Environment::get_graphics_api())
		{
		case GraphicsAPI::None: return nullptr;
		case GraphicsAPI::OpenGL: return CreateShared<OGL::OGL_RenderBuffer>(*this);
		}

		Debug::Log::error("Invalid GraphicsAPI");
		return nullptr;
	}
}