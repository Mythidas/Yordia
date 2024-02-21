#pragma once

#include "Yortek/Rendering/GraphicsContext.h"

namespace Yortek::Rendering::OGL
{
  class OGL_GraphicsContext : public GraphicsContext
  {
  public:
    OGL_GraphicsContext(const Builder& builder);

    virtual void swap_buffers() override;

  private:
    Builder m_builder;
  };
}