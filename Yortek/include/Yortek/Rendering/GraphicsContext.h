#pragma once

#include "Yortek/Core/Defines.h"
#include "Yortek/Tools/BuilderHelper.h"

namespace Yortek::Rendering
{
  class GraphicsContext
  {
  public:
    struct Builder : public Tools::BuilderHelper<Builder>
    {
      void* window_handle{ nullptr };

      Builder& set_window_handle(void* handle) { return _set_prop(window_handle, handle); }
      Unique<GraphicsContext> build() const;
    };

    virtual void swap_buffers() = 0;
  };
}