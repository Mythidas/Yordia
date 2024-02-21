#include <Yortek/Core/Application.h>
#include <Yortek/Rendering/Renderer2D.h>
#include <Yortek/Debug/Log.h>
#include <iostream>

Yortek::Math::Transform transform;
Yortek::Rendering::Camera* camera;

void on_update()
{
  Yortek::Debug::Log::trace("Update Callback");
  Yortek::Rendering::Renderer2D::begin_frame(*camera, transform);
  Yortek::Rendering::Renderer2D::draw_quad({ 0.0f }, { 0.0f }, { 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f});
  Yortek::Rendering::Renderer2D::end_frame();
}

int main()
{
  using namespace Yortek;

  Application::Specs specs;
  specs.graphics_api = GraphicsAPI::OpenGL;
  specs.window = Window::Builder()
    .set_title("Yordia")
    .set_width(1280)
    .set_height(720)
    .set_vsync(false)
    .set_fixed_aspect_ratio(true);

  Application::start(specs);

  // Place Application Logic
  
  camera = new Yortek::Rendering::Camera(1280, 720);
  camera->clear_color = { 0.2f, 0.3f, 0.5f, 1.0f };
  transform.position.z = -5.0f;
  Application::ev_OnUpdate += on_update;

  // -----------------------

  Application::run();
  Application::stop();
  return 0;
}