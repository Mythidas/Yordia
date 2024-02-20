#pragma once

#include "Yortek/Graphics/GraphicsContext.h"

namespace Yortek::OGL
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