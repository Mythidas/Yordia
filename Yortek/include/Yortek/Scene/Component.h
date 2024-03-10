#pragma once

#include "Yortek/Scene/Entity.h"

namespace Yortek::Scene
{
  class Registry;

  class Component
  {
  public:
    Entity& get_entity() { return m_entity; }
    Registry& get_registry() { return *m_registry; }

  private:
    friend class Registry;
    Entity m_entity;
    Registry* m_registry;
  };
}