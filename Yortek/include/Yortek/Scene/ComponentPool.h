#pragma once

#include "Yortek/Reflection/Type.h"

namespace Yortek::Scene
{
  class ComponentPool
  {
  public:
    ComponentPool(size_t size);
    ~ComponentPool();

    void* get_data(size_t index);

  private:
    size_t m_size;
    char* m_data;
  };
}