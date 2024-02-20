#pragma once

namespace Yortek
{
  template <typename T>
  class Singleton
  {
  public:
    Singleton();
    ~Singleton();

    static T& instance() { return *s_instance; }

  protected:
    friend T;
    inline static T* s_instance;
  };

  template<typename T>
  inline Singleton<T>::Singleton()
  {
    if (s_instance) return;
    s_instance = static_cast<T*>(this);
  }

  template<typename T>
  inline Singleton<T>::~Singleton()
  {
    if (s_instance == this)
      s_instance = nullptr;
  }
}