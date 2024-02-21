#include "Yortek/Core/Application.h"

#include <stdexcept>

namespace Yortek
{
  Event<> Application::ev_OnUpdate;

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

    s_window = specs.window.build();
    s_window->ev_OnWindowClose += _on_close;
  }

  void Application::run()
  {
    s_running = true;

    while (s_running)
    {
      s_window->update();
      ev_OnUpdate.dispatch();
    }
  }

  void Application::stop()
  {
    s_window->ev_OnWindowClose -= _on_close;
    delete s_instance;
  }

  void Application::_on_close()
  {
    s_running = false;
  }
}