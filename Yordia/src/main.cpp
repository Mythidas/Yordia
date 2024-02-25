#include <Yortek/Core/Application.h>
#include <Yortek/Core/Input.h>
#include <Yortek/Core/Time.h>
#include <Yortek/Rendering/Renderer2D.h>
#include <Yortek/Debug/Log.h>
#include <Yortek/Reflection/Type.h>
#include <Yortek/Scene/Registry.h>

#include <iostream>

using namespace Yortek;

Yortek::Math::Transform transform;
Yortek::Rendering::Camera* camera;
Yortek::Math::Vector3 position;
Yortek::Scene::Registry registry;
Shared<Rendering::Image> texture;

void on_update()
{
  if (Yortek::Input::is_key_pressed(Yortek::KeyCode::W))
  {
    position.x += 1.0f * Yortek::Time::get_delta_time();
  }

  Yortek::Rendering::Renderer2D::begin_frame(*camera, transform);
  Yortek::Rendering::Renderer2D::draw_quad(position, { 0.0f }, { 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f});
  Yortek::Rendering::Renderer2D::draw_quad({ 0.5f }, { 0.0f }, { 0.7f }, {1.0f, 0.2f, 1.0f, 1.0f}, texture);
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
  
  Application::ev_OnUpdate += on_update;
  texture = Rendering::Image::Builder().build();
  texture->load_data("../Assets/Textures/icons8-file.png");
  camera = new Yortek::Rendering::Camera(1280, 720);
  camera->clear_color = { 0.2f, 0.3f, 0.5f, 1.0f };
  transform.position.z = -5.0f;

  // -----------------------

  Application::run();
  Application::stop();
  return 0;
}