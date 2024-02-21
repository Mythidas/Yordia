#include <Yortek/Core/Application.h>
#include <Yortek/Debug/Log.h>
#include <iostream>

void on_update()
{
  // Yortek::Debug::Log::trace("Update Callback");
}

int main()
{
  using namespace Yortek;

  Application::Specs specs;
  specs.backend = ApplicationBackend::OpenGL;
  specs.window = Window::Builder()
    .set_title("Yordia")
    .set_width(1280)
    .set_height(720)
    .set_vsync(false)
    .set_fixed_aspect_ratio(true);

  Application::start(specs);

  // Place Application Logic
  
  Application::ev_OnUpdate += on_update;

  // -----------------------

  Application::run();
  Application::stop();
  return 0;
}