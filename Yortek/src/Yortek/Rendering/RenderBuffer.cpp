#include "Yortek/Rendering/RenderBuffer.h"
#include "Yortek/Core/Application.h"
#include "Platform/OpenGL/OGL_RenderBuffer.h"

namespace Yortek::Rendering
{
	Shared<RenderBuffer> RenderBuffer::Builder::build() const
	{
		switch (Application::get_backend())
		{
		case ApplicationBackend::None: return nullptr;
		case ApplicationBackend::OpenGL: return CreateShared<OGL::OGL_RenderBuffer>(*this);
		}

		return nullptr;
	}
}