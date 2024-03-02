#include <Yortek/Core/Application.h>
#include <Yortek/Core/Input.h>
#include <Yortek/Core/Time.h>
#include <Yortek/Rendering/Renderer2D.h>
#include <Yortek/Debug/Log.h>
#include <Yortek/Reflection/Type.h>
#include <Yortek/Scene/Registry.h>
#include <Yortek/Scene/JobScheduler.h>

#include <iostream>

using namespace Yortek;

Yortek::Math::Transform transform;
Yortek::Rendering::Camera* camera;
Yortek::Scene::Registry registry;
Shared<Rendering::Image> texture;

struct PosComp : public Scene::Component
{
  float x, y, z;
};

class PosJob : public Scene::IJob
{
public:
  virtual void on_update(Scene::Registry& registry)
  {
    if (Yortek::Input::is_key_pressed(Yortek::KeyCode::W))
    {
      for (auto ent : registry.get_view<PosComp>())
      {
        auto pos = registry.get_component<PosComp>(ent);
        pos->x += 3.0f * Time::get_delta_time();
      }
    }
  }
};
YOR_REGISTER_JOB(PosJob)

Scene::Entity ent;
Scene::Ref<PosComp> position;

void on_update()
{
  Yortek::Rendering::Renderer2D::begin_frame(*camera, transform);
  Yortek::Rendering::Renderer2D::draw_quad({ position->x, position->y, position->z }, {0.0f}, {1.0f}, {1.0f, 1.0f, 1.0f, 1.0f});
  Yortek::Rendering::Renderer2D::draw_quad({ 0.5f }, { 0.0f }, { 0.7f }, {1.0f, 0.2f, 1.0f, 1.0f}, texture);
  Yortek::Rendering::Renderer2D::end_frame();

  registry.on_update();
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

  ent = registry.create_ent();
  position = registry.add_component<PosComp>(ent);

  // -----------------------

  Application::run();
  Application::stop();
  return 0;
}