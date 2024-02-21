#include "Yortek/Rendering/GraphicsContext.h"
#include "Yortek/Core/Environment.h"
#include "Yortek/Debug/Log.h"
#include "Platform/None/N_GraphicsContext.h"
#include "Platform/OpenGL/OGL_GraphicsContext.h"

namespace Yortek::Rendering
{
  Unique<GraphicsContext> GraphicsContext::Builder::build() const
  {
    switch (Environment::get_graphics_api())
    {
    case GraphicsAPI::None: return CreateUnique<None::N_GraphicsContext>(*this);
    case GraphicsAPI::OpenGL: return CreateUnique<OGL::OGL_GraphicsContext>(*this);
    }

    Debug::Log::error("Invalid GraphicsAPI!");
    return nullptr;
  }
}