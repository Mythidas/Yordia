#include "Yortek/Scene/Registry.h"
#include "Yortek/Debug/Log.h"
#include "Yortek/Scene/JobScheduler.h"

namespace Yortek::Scene
{
  Registry::~Registry()
  {
    m_pools.clear();
  }

  Entity Registry::create_ent(std::string name)
  {
    if (!m_free_entity_indices.empty())
    {
      size_t old_index = m_free_entity_indices.back();
      m_free_entity_indices.pop_back();

      m_entities[old_index].id = UUID();
      m_entities[old_index].components.reset();
      m_id_to_index[m_entities[old_index].id] = old_index;
      return m_entities[old_index];
    }

    m_entities[m_entity_counter].id = UUID();
    m_entities[m_entity_counter].components.reset();
    m_id_to_index[m_entities[m_entity_counter].id] = m_entity_counter;
    m_entity_counter++;
    return m_entities[m_entity_counter - 1];
  }

  void Registry::destroy_ent(const Entity& ent)
  {
    if (!_is_valid_entity(ent)) return;

    m_free_entity_indices.push_back(m_id_to_index[ent.id]);
    m_entities[m_id_to_index[ent.id]].id = UUID::INVALID;
    m_id_to_index.erase(ent.id);
  }

  void Registry::on_update()
  {
    JobScheduler::instance().dispatch_jobs(*this);
  }

  void* Registry::add_component(const TypeID& id, const size_t& size, const Entity& ent)
  {
    if (!_is_valid_entity(ent)) return nullptr;

    if (m_pools.size() >= MAX_COMPONENTS)
      return nullptr;

    if (!m_pools.contains(id))
    {
      m_pools[id] = new ComponentPool(size, m_pools.size());
    }

    m_entities[m_id_to_index[ent.id]].components.set(m_pools[id]->get_mask_id());
    return m_pools[id]->get_data(m_id_to_index[ent.id]);;
  }

  void* Registry::get_component(const TypeID& id, const Entity& ent)
  {
    if (!_is_valid_entity(ent)) return nullptr;
    if (!m_pools.contains(id)) return nullptr;

    if (m_entities[m_id_to_index[ent.id]].components.test(m_pools[id]->get_mask_id()))
      return m_pools[id]->get_data(m_id_to_index[ent.id]);

    return nullptr;
  }

  bool Registry::has_component(const TypeID& id, const Entity& ent)
  {
    if (!_is_valid_entity(ent)) return false;
    if (!m_pools.contains(id)) return false;

    if (m_entities[m_id_to_index[ent.id]].components.test(m_pools[id]->get_mask_id()))
      return true;

    return false;
  }

  void Registry::remove_component(const TypeID& id, const Entity& ent)
  {
    if (!_is_valid_entity(ent)) return;
    if (!m_pools.contains(id)) return;
    m_entities[m_id_to_index[ent.id]].components.reset(m_pools[id]->get_mask_id());
  }

  bool Registry::_is_valid_entity(const Entity& ent)
  {
    return ent.id.valid() && m_id_to_index.contains(ent.id);
  }

  size_t Registry::_find_pool_id(const TypeID& component)
  {
    if (m_pools.contains(component))
      return m_pools[component]->get_mask_id();

    return INVALID_TYPE;
  }
}