#include "Yortek/Rendering/RenderCommands.h"
#include "Yortek/Core/Application.h"
#include "Platform/OpenGL/OGL_RenderCommands.h"

namespace Yortek::Rendering
{
	Unique<RenderCommands> RenderCommands::Builder::build() const
	{
		switch (Application::get_backend())
		{
		case ApplicationBackend::None: return nullptr;
		case ApplicationBackend::OpenGL: return CreateUnique<OGL::OGL_RenderCommands>();
		}

		return nullptr;
	}
}