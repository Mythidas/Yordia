#pragma once

#include "Yortek/Scene/Entity.h"
#include "Yortek/Scene/ComponentPool.h"
#include "Yortek/Reflection/Type.h"
#include "Yortek/Scene/Ref.h"

#include <unordered_map>

namespace Yortek::Scene
{
  class Registry
  {
  public:
    Entity create_ent(std::string name = "Empty Entity");
    void destroy_ent(const Entity& ent);

    void on_update();

    void* add_component(const TypeID& id, const Entity& ent);
    void* get_component(const TypeID& id, const Entity& ent);
    void remove_component(const TypeID& id, const Entity& ent);

    template <typename T>
    Ref<T> add_component(const Entity& ent);
    template <typename T>
    Ref<T> get_component(const Entity& ent);
    template <typename T>
    void remove_component(const Entity& ent);

  private:
    bool _is_valid_entity(const Entity& ent);

  private:
    Entity m_entities[MAX_ENTITIES];
    std::vector<size_t> m_free_entity_indices;
    std::unordered_map<UUID, size_t> m_id_to_index;
    std::unordered_map<TypeID, ComponentPool> m_pools;
  };

  template<typename T>
  inline Ref<T> Registry::add_component(const Entity& ent)
  {
    void* comp = add_component(Reflection::Type<T>().id(), ent);
    return Ref<T>(ent.id, comp);
  }

  template<typename T>
  inline Ref<T> Registry::get_component(const Entity& ent)
  {
    void* comp = get_component(Reflection::Type<T>().id(), ent);
    return Ref<T>(ent.id, comp);
  }

  template<typename T>
  inline void Registry::remove_component(const Entity& ent)
  {
    remove_component(Reflection::Type<T>().id(), ent);
  }
}