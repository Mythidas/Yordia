#include "Yortek/Rendering/Shader.h"
#include "Yortek/Core/Environment.h"
#include "Yortek/Debug/Log.h"
#include "Platform/OpenGL/OGL_Shader.h"

namespace Yortek::Rendering
{
	Shared<Shader> Shader::Builder::build() const
	{
		switch (Environment::get_graphics_api())
		{
		case GraphicsAPI::None: return nullptr;
		case GraphicsAPI::OpenGL: return CreateShared<OGL::OGL_Shader>(*this);
		}

		Debug::Log::error("Invalid GraphicsAPI");
		return nullptr;
	}
}