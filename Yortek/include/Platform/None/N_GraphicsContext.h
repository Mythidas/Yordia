#pragma once

#include "Yortek/Rendering/GraphicsContext.h"

namespace Yortek::Rendering::None
{
  class N_GraphicsContext : public GraphicsContext
  {
  public:
    N_GraphicsContext(const Builder& builder) {}

    virtual void swap_buffers() override {}
  };
}