#include "Yortek/Rendering/GraphicsContext.h"
#include "Yortek/Core/Application.h"
#include "Yortek/Debug/Log.h"
#include "Platform/None/N_GraphicsContext.h"
#include "Platform/OpenGL/OGL_GraphicsContext.h"

namespace Yortek::Rendering
{
  Unique<GraphicsContext> GraphicsContext::Builder::build() const
  {
    switch (Application::get_backend())
    {
    case ApplicationBackend::None: return CreateUnique<None::N_GraphicsContext>(*this);
    case ApplicationBackend::OpenGL: return CreateUnique<OGL::OGL_GraphicsContext>(*this);
    }

    Debug::Log::error("Invalid Application backend!");
    return nullptr;
  }
}