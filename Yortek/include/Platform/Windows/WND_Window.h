#pragma once

#include "Yortek/Core/Window.h"
#include "Yortek/Rendering/GraphicsContext.h"

struct GLFWwindow;

namespace Yortek::WND
{
  class WND_Window : public Window
  {
  public:
    WND_Window(const Builder& builder);
    ~WND_Window();

    virtual void update() override;

    virtual std::string get_title() const override { return m_builder.title; }
    virtual uint32_t get_width() const override { return m_builder.width; }
    virtual uint32_t get_height() const override { return m_builder.height; }
    virtual void* get_native_window() const override { return m_window; }

    virtual void set_title(const std::string& title) override;
    virtual void set_cursor(bool locked) override;

  private:
    Builder m_builder;
    GLFWwindow* m_window;
    Unique<Rendering::GraphicsContext> m_graphics_context;
  };
}