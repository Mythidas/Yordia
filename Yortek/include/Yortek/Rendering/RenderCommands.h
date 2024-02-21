#pragma once

#include "Yortek/Core/Defines.h"
#include "Yortek/Tools/Singleton.h"

namespace Yortek::Rendering
{
  class RenderCommands : public Tools::Singleton<RenderCommands, true>
  {
  public:
    struct Builder
    {
      Unique<RenderCommands> build() const;
    };

    static void enable_depth_testing(bool enable) { instance()._enable_depth_testing_impl(enable); }
    static void clear_color(float r, float g, float b) { instance()._clear_color_impl(r, g, b); }
    static void resize(int width, int height) { instance()._resize_impl(width, height); }

  protected:
    virtual void _enable_depth_testing_impl(bool enable) = 0;
    virtual void _clear_color_impl(float r, float g, float b) = 0;
    virtual void _resize_impl(int width, int height) = 0;
  };
}