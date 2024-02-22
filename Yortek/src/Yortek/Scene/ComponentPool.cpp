#include "Yortek/Scene/ComponentPool.h"
#include "Yortek/Scene/Entity.h"

namespace Yortek::Scene
{
  ComponentPool::ComponentPool(size_t size)
    : m_size(size)
  {
    m_data = new char[size * MAX_ENTITIES];
  }

  ComponentPool::~ComponentPool()
  {
    delete[] m_data;
  }

  void* ComponentPool::get_data(size_t index)
  {
    if (index >= MAX_ENTITIES) return nullptr;
    return m_data + index * m_size;
  }
}