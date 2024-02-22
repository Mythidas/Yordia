#pragma once

#include "Yortek/Core/UUID.h"

#include <bitset>

namespace Yortek::Scene
{
  static const int MAX_ENTITIES = 1000;
  using ComponentMask = std::bitset<32>;

  class Entity
  {
  public:
    UUID id;
    ComponentMask components;
  };
}