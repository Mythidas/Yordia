#pragma once

#include "Yortek/Graphics/GraphicsContext.h"

namespace Yortek::None
{
  class N_GraphicsContext : public GraphicsContext
  {
  public:
    N_GraphicsContext(const Builder& builder) {}

    virtual void swap_buffers() override {}
  };
}