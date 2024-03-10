#include <Yortek/Core/Application.h>
#include <Yortek/Core/Input.h>
#include <Yortek/Core/Time.h>
#include <Yortek/Rendering/Renderer2D.h>
#include <Yortek/Debug/Log.h>
#include <Yortek/Reflection/Type.h>
#include <Yortek/Scene/Registry.h>
#include <Yortek/Scene/JobScheduler.h>
#include <Yortek/Components/Transform.h>
#include <Yortek/Components/SpriteRenderer.h>
#include <Yortek/Components/Camera.h>
#include <Yortek/Jobs/Scene2DRenderJob.h>

#include <iostream>

using namespace Yortek;

Yortek::Scene::Registry registry;

class CharacterController : public Scene::Behavior
{
public:
  Scene::Ref<Components::Transform> pos;

  virtual void on_attach() override
  {
    pos = get_registry().get_component<Components::Transform>(get_entity());
  }

  virtual void on_update() override
  {
    if (!pos) return;

    if (Yortek::Input::is_key_pressed(Yortek::KeyCode::W))
      pos->position.y += 3.0f * Time::get_delta_time();

    if (Yortek::Input::is_key_pressed(Yortek::KeyCode::S))
      pos->position.y -= 3.0f * Time::get_delta_time();

    if (Yortek::Input::is_key_pressed(Yortek::KeyCode::A))
      pos->position.x -= 3.0f * Time::get_delta_time();

    if (Yortek::Input::is_key_pressed(Yortek::KeyCode::D))
      pos->position.x += 3.0f * Time::get_delta_time();
  }
};

Scene::Entity spriteEnt;
Scene::Ref<Components::Transform> spriteTrans;
Scene::Ref<Components::SpriteRenderer> sprite;

Scene::Entity cameraEnt;
Scene::Ref<Components::Transform> cameraTrans;
Scene::Ref<Components::Camera> cameraComp;

void on_update()
{
  registry.on_update();
}

void on_resize(int w, int h)
{
  cameraComp->info.resize(w, h);
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
  Application::ev_OnResize += on_resize;

  spriteEnt = registry.create_ent();
  spriteTrans = registry.add_component<Components::Transform>(spriteEnt);
  sprite = registry.add_component<Components::SpriteRenderer>(spriteEnt);
  registry.add_behavior<CharacterController>(spriteEnt);

  cameraEnt = registry.create_ent();
  cameraTrans = registry.add_component<Components::Transform>(cameraEnt);
  cameraComp = registry.add_component<Components::Camera>(cameraEnt);

  cameraTrans->position.z = -5.0f;
  cameraComp->info.clear_color = { 0.2f, 0.3f, 0.5f, 1.0f };

  on_resize(1280, 720);

  // -----------------------

  Application::run();
  Application::stop();
  return 0;
}