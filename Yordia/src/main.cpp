#include <Yortek/Core/Application.h>
#include <iostream>

int main()
{
  using namespace Yortek;

  Application::start({ ApplicationBackend::OpenGL });
  Application::run();
  Application::stop();
  return 0;
}