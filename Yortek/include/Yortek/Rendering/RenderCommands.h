#pragma once

#include "Yortek/Core/Defines.h"
#include "Yortek/Rendering/Color.h"
#include "Yortek/Math/Vector2.h"
#include "Yortek/Tools/Singleton.h"

namespace Yortek::Rendering
{
  class RenderCommands : public Tools::Singleton<RenderCommands>
  {
  public:
    struct Builder
    {
      Unique<RenderCommands> build() const;
    };

    static void enable_depth_testing(bool enable) { instance()._enable_depth_testing_impl(enable); }
    static void enable_blending(bool enable) { instance()._enable_blending_impl(enable); }
    static void clear_color(Color color) { instance()._clear_color_impl(color.r, color.g, color.b); }
    static void resize(const Math::IVector2& size) { instance()._resize_impl(size.x, size.y); }

  protected:
    virtual void _enable_depth_testing_impl(bool enable) = 0;
    virtual void _enable_blending_impl(bool enable) = 0;
    virtual void _clear_color_impl(float r, float g, float b) = 0;
    virtual void _resize_impl(int width, int height) = 0;
  };
}