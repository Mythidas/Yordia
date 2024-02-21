#pragma once

namespace Yortek::Tools
{
  template <typename T, bool managed = false>
  class Singleton
  {
  private:
    Singleton();
    ~Singleton();

  public:
    static T& instance();

  protected:
    friend T;
    inline static T* s_instance;
  };

  template<typename T, bool managed>
  inline Singleton<T, managed>::Singleton()
  {
    if (s_instance) return;
    s_instance = static_cast<T*>(this);
  }

  template<typename T, bool managed>
  inline Singleton<T, managed>::~Singleton()
  {
    if (s_instance == this)
    {
      if (managed)
        delete s_instance;

      s_instance = nullptr;
    }
  }

  template<typename T, bool managed>
  inline T& Singleton<T, managed>::instance()
  {
    if (managed && !s_instance)
      s_instance = new T();
    return *s_instance;
  }
}