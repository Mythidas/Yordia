#pragma once

#include "Yortek/Scene/Registry.h"

namespace Yortek::Scene
{
  class IJob
  {
  public:
    virtual void on_update(Registry& registry) = 0;
  };
}