#include "YTEngine/Graphics/GraphicsPipline.h"
#include "YTEngine/Core/Application.h"
#include "Platform/OpenGL/OGL_GraphicsPipeline.h"

namespace Yor
{
	Shared<GraphicsPipeline> GraphicsPipeline::Builder::build() const
	{
		switch (Application::getBackend())
		{
		case ApplicationBackend::None: return nullptr;
		case ApplicationBackend::OpenGL: return CreateShared<OGL::OGL_GraphicsPipeline>(*this);
		}

		return nullptr;
	}
}