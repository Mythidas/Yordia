#pragma once

#include "Yortek/Core/UUID.h"

#include <bitset>

namespace Yortek::Scene
{
  static const int MAX_ENTITIES = 1000;
  static const int MAX_COMPONENTS = 32;
  using ComponentMask = std::bitset<MAX_COMPONENTS>;

  class Entity
  {
  public:
    UUID id;
    ComponentMask components;
  };
}