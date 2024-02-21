#include "YTEngine/Graphics/RenderBuffer.h"
#include "YTEngine/Core/Application.h"
#include "Platform/OpenGL/OGL_RenderBuffer.h"

namespace Yor
{
	Shared<RenderBuffer> RenderBuffer::Builder::build() const
	{
		switch (Application::getBackend())
		{
		case ApplicationBackend::None: return nullptr;
		case ApplicationBackend::OpenGL: return CreateShared<OGL::OGL_RenderBuffer>(*this);
		}

		return nullptr;
	}
}