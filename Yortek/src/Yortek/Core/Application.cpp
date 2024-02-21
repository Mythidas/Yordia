#include "Yortek/Core/Application.h"
#include "Yortek/Core/Environment.h"
#include "Yortek/Core/Time.h"
#include "Yortek/Rendering/Renderer2D.h"

#include <stdexcept>

namespace Yortek
{
  Event<> Application::ev_OnUpdate;

  bool Application::s_running{ false };
  Unique<Window> Application::s_window{ nullptr };

  Application::Application()
  {
  }

  void Application::start(const Specs& specs)
  {
    if (s_instance) throw std::runtime_error("Application is already started!");
    s_instance = new Application();

    // setup environment
    Environment::s_gapi = specs.graphics_api;

    // create Window
    s_window = specs.window.build();
    s_window->ev_OnWindowClose += _on_close;

    // init rendering
    Rendering::Renderer2D::_construct();
  }

  void Application::run()
  {
    s_running = true;

    while (s_running)
    {
      Time::_tick();
      s_window->update();
      ev_OnUpdate.dispatch();
    }
  }

  void Application::stop()
  {
    s_window->ev_OnWindowClose -= _on_close;
    Rendering::Renderer2D::_destruct();
    delete s_instance;
  }

  void Application::_on_close()
  {
    s_running = false;
  }
}