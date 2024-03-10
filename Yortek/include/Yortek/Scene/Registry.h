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
    Registry() = default;
    ~Registry();

    Entity create_ent(std::string name = "Empty Entity");
    void destroy_ent(const Entity& ent);
    Entity find_ent(const UUID& uuid);

    void on_update();

    void* add_component(const TypeID& id, const size_t& size, const Entity& ent);
    void* get_component(const TypeID& id, const Entity& ent);
    bool has_component(const TypeID& id, const Entity& ent);
    void remove_component(const TypeID& id, const Entity& ent);

    template <typename T>
    Ref<T> add_component(const Entity& ent);
    template <typename T>
    Ref<T> get_component(const Entity& ent);
    template <typename T>
    bool has_component(const Entity& ent);
    template <typename T>
    void remove_component(const Entity& ent);

    void* get_behavior(const TypeID& id, const Entity& ent);
    bool has_behavior(const TypeID& id, const Entity& ent);

    template <typename T>
    Ref<T> add_behavior(const Entity& ent);
    template <typename T>
    Ref<T> get_behavior(const Entity& ent);
    template <typename T>
    bool has_behavior(const Entity& ent);
    template <typename T>
    void remove_behavior(const Entity& ent);

  public:
    template <typename ...Components>
    struct View
    {
    public:
      View(Registry& reg);

      struct Iterator
      {
      public:
        Iterator(bool all, size_t index, ComponentMask mask, Registry& reg)
          : m_all(all), m_index(index), m_mask(mask), m_reg(reg)
        {
        }

        Entity operator*() const
        {
          return m_reg.m_entities[m_index];
        }

        bool operator== (const Iterator& rhs) const
        {
          return m_index == rhs.m_index;
        }

        bool operator!= (const Iterator& rhs) const
        {
          return m_index != rhs.m_index;
        }

        Iterator& operator++ ()
        {
          do
          {
            m_index++;
          } while (m_index < m_reg.m_entity_counter && !_is_valid_index());
          return *this;
        }

      private:
        bool _is_valid_index()
        {
          if (!m_reg._is_valid_entity(m_reg.m_entities[m_index])) return false;
          return m_all || m_mask == (m_mask & m_reg.m_entities[m_index].components);
        }

        bool m_all;
        size_t m_index;
        ComponentMask m_mask;
        Registry& m_reg;
      };

      const Iterator begin() const;
      const Iterator end() const;

    private:
      bool m_all{ false };
      bool m_invalid{ false };
      ComponentMask m_mask;
      Registry& m_reg;
    };

    template <typename ...Components>
    View<Components...> get_view() { return View<Components...>(*this); }

  private:
    bool _is_valid_entity(const Entity& ent);
    bool _is_valid_entity(const UUID& ent);
    size_t _find_pool_id(const TypeID& component);

  private:
    Entity m_entities[MAX_ENTITIES];
    size_t m_entity_counter = 0;
    std::vector<size_t> m_free_entity_indices;
    std::unordered_map<UUID, size_t> m_id_to_index;
    std::unordered_map<TypeID, ComponentPool*> m_comp_pools;
    std::unordered_map<UUID, std::unordered_map<TypeID, Behavior*>> m_behaviors;
  };

  template<typename T>
  inline Ref<T> Registry::add_component(const Entity& ent)
  {
    static_assert(std::is_base_of_v<Component, T>, "T is not derived from Component!");
    static_assert(!std::is_base_of_v<Behavior, T>, "T cannot be a Behavior!");

    if (has_component<T>(ent))
    {
      return get_component<T>(ent);
    }

    T* comp = new (add_component(Reflection::Type<T>().id(), sizeof(T), ent)) T();
    static_cast<Component*>(comp)->m_entity = ent;
    static_cast<Component*>(comp)->m_registry = this;
    return Ref<T>(ent.id, comp, this);
  }

  template<typename T>
  inline Ref<T> Registry::get_component(const Entity& ent)
  {
    static_assert(std::is_base_of_v<Component, T>, "T is not derived from Component!");
    T* comp = static_cast<T*>(get_component(Reflection::Type<T>().id(), ent));
    return Ref<T>(ent.id, comp, this);
  }

  template<typename T>
  inline bool Registry::has_component(const Entity& ent)
  {
    static_assert(std::is_base_of_v<Component, T>, "T is not derived from Component!");
    return has_component(Reflection::Type<T>().id(), ent);
  }

  template<typename T>
  inline void Registry::remove_component(const Entity& ent)
  {
    static_assert(std::is_base_of_v<Component, T>, "T is not derived from Component!");
    remove_component(Reflection::Type<T>().id(), ent);
  }

  template<typename T>
  inline Ref<T> Registry::add_behavior(const Entity& ent)
  {
    static_assert(std::is_base_of_v<Behavior, T>, "T is not derived from Behavior!");
    if (!_is_valid_entity(ent)) return Ref<T>();

    if (has_behavior<T>(ent))
    {
      return get_behavior<T>(ent);
    }

    m_behaviors[ent.id][Reflection::Type<T>().id()] = new T();
    static_cast<Component*>(m_behaviors[ent.id][Reflection::Type<T>().id()])->m_entity = ent;
    static_cast<Component*>(m_behaviors[ent.id][Reflection::Type<T>().id()])->m_registry = this;
    m_behaviors[ent.id][Reflection::Type<T>().id()]->on_attach();
    return Ref<T>(ent.id, static_cast<T*>(m_behaviors[ent.id][Reflection::Type<T>().id()]), this);
  }

  template<typename T>
  inline Ref<T> Registry::get_behavior(const Entity& ent)
  {
    static_assert(std::is_base_of_v<Behavior, T>, "T is not derived from Behavior!");
    if (!_is_valid_entity(ent)) return Ref<T>();

    T* comp = static_cast<T*>(m_behaviors[ent.id][Reflection::Type<T>().id()]);
    return Ref<T>(ent.id, comp, this);
  }

  template<typename T>
  inline bool Registry::has_behavior(const Entity& ent)
  {
    static_assert(std::is_base_of_v<Behavior, T>, "T is not derived from Behavior!");
    if (!_is_valid_entity(ent)) return false;
    return m_behaviors[ent.id].contains(Reflection::Type<T>().id());
  }

  template<typename T>
  inline void Registry::remove_behavior(const Entity& ent)
  {
    static_assert(std::is_base_of_v<Behavior, T>, "T is not derived from Behavior!");
    if (!_is_valid_entity(ent)) return;

    m_behaviors[ent.id][Reflection::Type<T>().id()]->on_detach();
    delete m_behaviors[ent.id][Reflection::Type<T>().id()];
    m_behaviors[ent.id].erase(Reflection::Type<T>().id());
  }

  template<typename ...Components>
  inline Registry::View<Components...>::View(Registry& reg)
    : m_reg(reg)
  {
    // TODO: Figure out if we can use static assert to make sure we are entering correct types
    
    if (sizeof...(Components) <= 0)
    {
      m_all = true;
    }
    else
    {
      size_t component_ids[] = { 0, m_reg._find_pool_id(Reflection::Type<Components>().id())... };
      for (size_t i = 1; i < (sizeof...(Components) + 1); i++)
      {
        if (component_ids[i] != INVALID_TYPE)
        {
          m_mask.set(component_ids[i]);
        }
        else
        {
          m_invalid = true;
          break;
        }
      }
    }
  }

  template<typename ...Components>
  inline const Registry::View<Components...>::Iterator Registry::View<Components...>::begin() const
  {
    size_t first = m_invalid ? m_reg.m_entity_counter : 0;
    while (first < m_reg.m_entity_counter &&
      (m_mask != (m_mask & m_reg.m_entities[first].components) ||
        !m_reg._is_valid_entity(m_reg.m_entities[first])))
    {
      first++;
    }

    return Iterator(m_all, first, m_mask, m_reg);
  }

  template<typename ...Components>
  inline const Registry::View<Components...>::Iterator Registry::View<Components...>::end() const
  {
    return Iterator(m_all, m_reg.m_entity_counter, m_mask, m_reg);
  }
}