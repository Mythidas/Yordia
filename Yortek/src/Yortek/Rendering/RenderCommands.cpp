#include "Yortek/Rendering/RenderCommands.h"
#include "Yortek/Core/Environment.h"
#include "Yortek/Debug/Log.h"
#include "Platform/OpenGL/OGL_RenderCommands.h"

namespace Yortek::Rendering
{
	Unique<RenderCommands> RenderCommands::Builder::build() const
	{
		switch (Environment::get_graphics_api())
		{
		case GraphicsAPI::None: return nullptr;
		case GraphicsAPI::OpenGL: return CreateUnique<OGL::OGL_RenderCommands>();
		}

		Debug::Log::error("Invalid GraphicsAPI");
		return nullptr;
	}
}