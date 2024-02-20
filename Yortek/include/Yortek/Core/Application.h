#pragma once

#include "Yortek/Core/Defines.h"
#include "Yortek/Core/Window.h"
#include "Yortek/Tools/Singleton.h"
#include "Yortek/Tools/Event.h"

namespace Yortek
{
  enum class ApplicationBackend
  {
    None,
    OpenGL
  };

  class Application : public Singleton<Application>
  {
  private:
    Application();

  public:
    struct Specs
    {
      ApplicationBackend backend{ ApplicationBackend::OpenGL };
    };

    static void start(const Specs& specs);
    static void run();
    static void stop();

    static ApplicationBackend get_backend() { return s_specs.backend; }
    static Unique<Window>& get_window() { return s_window; }

  private:
    static bool _on_close();

  private:
    static Specs s_specs;
    static bool s_running;
    static Unique<Window> s_window;
  };
}