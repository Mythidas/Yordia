#include "YTEngine/Graphics/Framebuffer.h"
#include "YTEngine/Core/Application.h"
#include "Platform/OpenGL/OGL_Framebuffer.h"

namespace Yor
{
	Shared<Framebuffer> Framebuffer::Builder::build() const
	{
		switch (Application::getBackend())
		{
		case ApplicationBackend::None: return nullptr;
		case ApplicationBackend::OpenGL: return CreateShared<OGL::OGL_Framebuffer>(*this);
		}

		return nullptr;
	}
}