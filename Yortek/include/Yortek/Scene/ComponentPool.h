#pragma once

#include "Yortek/Reflection/Type.h"

namespace Yortek::Scene
{
  class ComponentPool
  {
  public:
    ComponentPool(size_t size, size_t id);
    ~ComponentPool();

    void* get_data(size_t index);
    size_t get_mask_id();

  private:
    size_t m_size;
    size_t m_id;
    char* m_data;
  };
}