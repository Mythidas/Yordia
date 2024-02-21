#include <Yortek/Core/Application.h>
#include <iostream>

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
  


  // -----------------------

  Application::run();
  Application::stop();
  return 0;
}