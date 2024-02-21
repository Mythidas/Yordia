#pragma once

#include "Yortek/Rendering/RenderCommands.h"

namespace Yortek::Rendering::OGL
{
  class OGL_RenderCommands : public RenderCommands
  {
  public:
    OGL_RenderCommands() = default;

  protected:
    virtual void _enable_depth_testing_impl(bool enable) override;
    virtual void _enable_blending_impl(bool enable) override;
    virtual void _clear_color_impl(float r, float g, float b) override;
    virtual void _resize_impl(int width, int height) override;
  };
}