#pragma once

#include "Yortek/Reflection/Type.h"
#include "Yortek/Scene/Entity.h"
#include "Yortek/Scene/Component.h"

namespace Yortek::Scene
{
  class RefHelper
  {
  public:
    static bool is_ref_valid(const TypeID& id, const UUID& ent_id);
    static void* get_ref_data(const TypeID& id, const UUID& ent_id);
  };

  template <typename T>
  class Ref
  {
  public:
    Ref() = default;
    Ref(const UUID& id) : m_id(id) {}
    Ref(T* ref) : m_ref(ref) {}
    Ref(const UUID& id, T* ref) : m_id(id), m_ref(ref) {}

    bool is_valid() const;

    T* operator->() const;
    T& operator*() const;

    static_assert(std::is_base_of_v<Component, T>, "Ref<T> is not derived from Component!");

  private:
    UUID m_id{ UUID::INVALID };
    T* m_ref{ nullptr };
  };

  template<typename T>
  inline bool Ref<T>::is_valid() const
  {
    return RefHelper::is_ref_valid(Reflection::Type<T>().id(), m_id);
  }

  template<typename T>
  inline T* Ref<T>::operator->() const
  {
    if (m_ref) return m_ref;
    return static_cast<T*>(RefHelper::get_ref_data(Reflection::Type<T>().id(), m_id));
  }

  template<typename T>
  inline T& Ref<T>::operator*() const
  {
    return *m_ref;
  }
}