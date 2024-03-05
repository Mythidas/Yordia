#pragma once

#include "Yortek/Scene/Component.h"
#include "Yortek/Rendering/CameraInfo.h"

namespace Yortek::Components
{
  struct Camera : public Scene::Component
  {
    Rendering::CameraInfo info;
  };
}