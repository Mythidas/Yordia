#pragma once

namespace Yortek
{
  template <typename B>
  class BuilderHelper
  {
  protected:
    template<typename T>
    B& _set_prop(T& prop, const T& value);
  };

  template <typename B>
  template<typename T>
  inline B& BuilderHelper<B>::_set_prop(T& prop, const T& value)
  {
    prop = value;
    return *static_cast<B*>(this);
  }
}