#include "Yortek/Jobs/Scene2DRenderJob.h"
#include "Yortek/Components/SpriteRenderer.h"
#include "Yortek/Components/Camera.h"
#include "Yortek/Components/Transform.h"
#include "Yortek/Rendering/Renderer2D.h"

namespace Yortek::Jobs
{
  void Scene2DRenderJob::on_update(Scene::Registry& registry)
  {
    Scene::Ref<Components::Camera> camera;
    Scene::Ref<Components::Transform> transform;
    for (auto ent : registry.get_view<Components::Camera, Components::Transform>())
    {
      camera = registry.get_component<Components::Camera>(ent);
      transform = registry.get_component<Components::Transform>(ent);
    }
    if (!camera && !transform) return;

    Rendering::Renderer2D::begin_frame(camera->info, *transform);
    for (auto ent : registry.get_view<Components::SpriteRenderer, Components::Transform>())
    {
      auto spriteRenderer = registry.get_component<Components::SpriteRenderer>(ent);
      auto spriteTransform = registry.get_component<Components::Transform>(ent);
      if (spriteRenderer)
      {
        if (spriteRenderer->sprite)
        {
          Rendering::Renderer2D::draw_quad(spriteTransform->position, spriteTransform->rotation, spriteTransform->scale, spriteRenderer->color, spriteRenderer->sprite);
        }
        else
        {
          Rendering::Renderer2D::draw_quad(spriteTransform->position, spriteTransform->rotation, spriteTransform->scale, spriteRenderer->color);
        }
      }
    }
    Rendering::Renderer2D::end_frame();
  }
}