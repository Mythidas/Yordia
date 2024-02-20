#pragma once

#include "Yortek/Core/Defines.h"
#include "Yortek/Tools/BuilderHelper.h"

namespace Yortek
{
  class GraphicsContext
  {
  public:
    struct Builder : public BuilderHelper<Builder>
    {
      void* window_handle{ nullptr };

      Builder& set_window_handle(void* handle) { return _set_prop(window_handle, handle); }
      Unique<GraphicsContext> build() const;
    };

    virtual void swap_buffers() = 0;
  };
}