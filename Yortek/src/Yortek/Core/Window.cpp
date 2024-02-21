#include "Yortek/Core/Window.h"
#include "Yortek/Core/Application.h"
#include "Yortek/Debug/Log.h"
#include "Platform/None/N_Window.h"
#include "Platform/Windows/WND_Window.h"

namespace Yortek
{
  Unique<Window> Window::Builder::build() const
  {
    switch (Environment::get_graphics_api())
    {
    case GraphicsAPI::None: return CreateUnique<None::N_Window>(*this);
    case GraphicsAPI::OpenGL: return CreateUnique<WND::WND_Window>(*this);
    }

    Debug::Log::error("Invalid Application backend!");
    return nullptr;
  }
}