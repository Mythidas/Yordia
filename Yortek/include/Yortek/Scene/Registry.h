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

  public:
    template <typename ...Components>
    struct View
    {
    public:
      View(Registry& reg)
        : m_reg(reg)
      {
        if (sizeof...(Components) <= 0)
        {
          m_all = true;
        }
        else
        {
          size_t component_ids[] = {0, m_reg._find_pool_id(Reflection::Type<Components>().id())... };
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

      const Iterator begin() const
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

      const Iterator end() const
      {
        return Iterator(m_all, m_reg.m_entity_counter, m_mask, m_reg);
      }

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
    size_t _find_pool_id(const TypeID& component);

  private:
    Entity m_entities[MAX_ENTITIES];
    size_t m_entity_counter = 0;
    std::vector<size_t> m_free_entity_indices;
    std::unordered_map<UUID, size_t> m_id_to_index;
    std::unordered_map<TypeID, ComponentPool*> m_pools;
  };

  template<typename T>
  inline Ref<T> Registry::add_component(const Entity& ent)
  {
    if (has_component<T>(ent))
    {
      return get_component<T>(ent);
    }

    T* comp = new (add_component(Reflection::Type<T>().id(), sizeof(T), ent)) T();
    return Ref<T>(ent.id, comp);
  }

  template<typename T>
  inline Ref<T> Registry::get_component(const Entity& ent)
  {
    T* comp = static_cast<T*>(get_component(Reflection::Type<T>().id(), ent));
    return Ref<T>(ent.id, comp);
  }

  template<typename T>
  inline bool Registry::has_component(const Entity& ent)
  {
    return has_component(Reflection::Type<T>().id(), ent);
  }

  template<typename T>
  inline void Registry::remove_component(const Entity& ent)
  {
    remove_component(Reflection::Type<T>().id(), ent);
  }
}