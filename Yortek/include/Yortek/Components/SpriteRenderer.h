#pragma once

#include "Yortek/Scene/Component.h"
#include "Yortek/Rendering/Image.h"
#include "Yortek/Rendering/Color.h"

namespace Yortek::Components
{
  struct SpriteRenderer : public Scene::Component
  {
    Rendering::Color color;
    Shared<Rendering::Image> sprite;
  };
}