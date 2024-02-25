#include "Yortek/Scene/ComponentPool.h"
#include "Yortek/Scene/Entity.h"

namespace Yortek::Scene
{
  ComponentPool::ComponentPool(size_t size, size_t id)
    : m_size(size), m_id(id)
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

  size_t ComponentPool::get_mask_id()
  {
    return m_id;
  }
}