#include "Yortek/Rendering/Framebuffer.h"
#include "Yortek/Core/Application.h"
#include "Platform/OpenGL/OGL_Framebuffer.h"

namespace Yortek::Rendering
{
	Shared<Framebuffer> Framebuffer::Builder::build() const
	{
		switch (Application::get_backend())
		{
		case ApplicationBackend::None: return nullptr;
		case ApplicationBackend::OpenGL: return CreateShared<OGL::OGL_Framebuffer>(*this);
		}

		return nullptr;
	}
}