#include "YTEngine/Graphics/RenderCommands.h"
#include "YTEngine/Core/Application.h"
#include "Platform/OpenGL/OGL_RenderCommands.h"

namespace Yor
{
	Unique<RenderCommands> RenderCommands::Builder::build() const
	{
		switch (Application::getBackend())
		{
		case ApplicationBackend::None: return nullptr;
		case ApplicationBackend::OpenGL: return CreateUnique<OGL::OGL_RenderCommands>();
		}

		return nullptr;
	}
}