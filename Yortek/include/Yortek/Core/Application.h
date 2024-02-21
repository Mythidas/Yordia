#pragma once

#include "Yortek/Core/Defines.h"
#include "Yortek/Core/Window.h"
#include "Yortek/Core/Event.h"
#include "Yortek/Core/Environment.h"
#include "Yortek/Tools/Singleton.h"

namespace Yortek
{
  class Application : public Tools::Singleton<Application>
  {
  private:
    Application();

  public:
    static Event<> ev_OnUpdate;

    struct Specs
    {
      Window::Builder window;
      GraphicsAPI graphics_api{ GraphicsAPI::OpenGL };
    };

  public:
    static void start(const Specs& specs);
    static void run();
    static void stop();

    static Unique<Window>& get_window() { return s_window; }

  private:
    static void _on_close();

  private:
    static bool s_running;
    static Unique<Window> s_window;
  };
}