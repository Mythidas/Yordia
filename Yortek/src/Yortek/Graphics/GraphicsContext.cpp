#include "Yortek/Graphics/GraphicsContext.h"
#include "Yortek/Core/Application.h"
#include "Platform/None/N_GraphicsContext.h"
#include "Platform/OpenGL/OGL_GraphicsContext.h"

namespace Yortek
{
  Unique<GraphicsContext> GraphicsContext::Builder::build() const
  {
    switch (Application::get_backend())
    {
    case ApplicationBackend::None: return CreateUnique<None::N_GraphicsContext>(*this);
    case ApplicationBackend::OpenGL: return CreateUnique<OGL::OGL_GraphicsContext>(*this);
    }

    // TODO: log error
    return nullptr;
  }
}