#include "Yortek/Core/Window.h"
#include "Yortek/Core/Application.h"
#include "Platform/None/N_Window.h"
#include "Platform/Windows/WND_Window.h"

namespace Yortek
{
  Unique<Window> Window::Builder::build() const
  {
    switch (Application::get_backend())
    {
    case ApplicationBackend::None: return CreateUnique<None::N_Window>(*this);
    case ApplicationBackend::OpenGL: return CreateUnique<WND::WND_Window>(*this);
    }
  }
}