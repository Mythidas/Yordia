#include "Yortek/Scene/Registry.h"

namespace Yortek::Scene
{
  Entity Registry::create_ent(std::string name)
  {
    return Entity();
  }

  void Registry::destroy_ent(const Entity& ent)
  {

  }

  void Registry::on_update()
  {
  }
  void* Registry::add_component(const TypeID& id, const Entity& ent)
  {
    return nullptr;
  }
  void* Registry::get_component(const TypeID& id, const Entity& ent)
  {
    return nullptr;
  }
  void Registry::remove_component(const TypeID& id, const Entity& ent)
  {
  }

  bool Registry::_is_valid_entity(const Entity& ent)
  {
    return ent.id.valid() && m_id_to_index.contains(ent.id);
  }
}