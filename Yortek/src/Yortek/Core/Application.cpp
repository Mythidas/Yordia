#include "Yortek/Core/Application.h"

#include <stdexcept>

namespace Yortek
{
  Application::Specs Application::s_specs;
  bool Application::s_running{ false };
  Unique<Window> Application::s_window{ nullptr };

  Application::Application()
  {
  }

  void Application::start(const Specs& specs)
  {
    if (s_instance) throw std::runtime_error("Application is already started!");
    s_specs = specs;
    s_instance = new Application();

    s_window = Window::Builder().build();
    s_window->OnWindowClose += _on_close;
  }

  void Application::run()
  {
    s_running = true;

    while (s_running)
    {
      s_window->update();
    }
  }

  void Application::stop()
  {
    s_window->OnWindowClose -= _on_close;
    delete s_instance;
  }

  bool Application::_on_close()
  {
    s_running = false;
    return false;
  }
}