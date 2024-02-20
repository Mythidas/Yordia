#pragma once

#include "Yortek/Core/Window.h"

namespace Yortek::None
{
  class N_Window : public Window
  {
  public:
    N_Window(const Builder& builder) {}

    virtual void update() override {}

    virtual std::string get_title() const override { return ""; }
    virtual uint32_t get_width() const override { return 0; }
    virtual uint32_t get_height() const override { return 0; }
    virtual void* get_native_window() const override { return nullptr; }

    virtual void set_title(const std::string& title) override {}
    virtual void set_cursor(bool locked) override {}
  };
}