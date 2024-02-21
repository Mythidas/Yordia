#pragma once

namespace Yortek
{
  enum class GraphicsAPI
  {
    None,
    OpenGL
  };

  class Environment
  {
  public:
    static GraphicsAPI get_graphics_api() { return s_gapi; }

  private:
    friend class Application;

  private:
    inline static GraphicsAPI s_gapi;
  };
}