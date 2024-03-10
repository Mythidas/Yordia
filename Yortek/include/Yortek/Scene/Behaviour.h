#pragma once

#include "Yortek/Scene/Component.h"

namespace Yortek::Scene
{
  class Behavior : public Component
  {
  public:
    virtual void on_attach() {}
    virtual void on_detach() {}
    virtual void on_update() {}
    virtual void on_fixed_update() {}
  };
}