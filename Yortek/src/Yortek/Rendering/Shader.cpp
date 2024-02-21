#include "Yortek/Rendering/Shader.h"
#include "Yortek/Core/Application.h"
#include "Platform/OpenGL/OGL_Shader.h"

namespace Yortek::Rendering
{
	Shared<Shader> Shader::Builder::build() const
	{
		switch (Application::get_backend())
		{
		case ApplicationBackend::None: return nullptr;
		case ApplicationBackend::OpenGL: return CreateShared<OGL::OGL_Shader>(*this);
		}

		return nullptr;
	}
}