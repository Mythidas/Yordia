#pragma once

#include "Yortek/Core/Defines.h"
#include "Yortek/Tools/Event.h"
#include "Yortek/Tools/BuilderHelper.h"

#include <string>

namespace Yortek
{
  enum class WindowState
  {
    Windowed,
    Minimized,
    Fullscreen
  };

  class Window
  {
  public:
    Event<> OnWindowClose; // No arguments
    Event<int, int> OnWindowResize; // Width, Height
    Event<int> OnKeyPressed; // Key
    Event<int> OnKeyReleased; // Key
    Event<double, double> OnMouseMoved; // Mouse X, Mouse Y
    Event<float> OnMouseScrolled; // Direction
    Event<int> OnMouseButtonPressed; // Button
    Event<int> OnMouseButtonReleased; // Button

    struct Builder : public BuilderHelper<Builder>
    {
      std::string title{ "AxtonEngine" };
      uint32_t width{ 1280 };
      uint32_t height{ 720 };
      bool fixed_aspect_ratio{ true };
      bool vsync{ false };

      Builder& set_title(const std::string& _title) { return _set_prop(title, _title); }
      Builder& set_width(uint32_t _width) { return _set_prop(width, _width); }
      Builder& set_height(uint32_t _height) { return _set_prop(height, _height); }
      Builder& set_fixed_aspect_ratio(bool _ratio) { return _set_prop(fixed_aspect_ratio, _ratio); }
      Builder& set_vsync(bool _vsync) { return _set_prop(vsync, _vsync); }
      Unique<Window> build() const;
    };

    virtual void update() = 0;

    virtual std::string get_title() const = 0;
    virtual uint32_t get_width() const = 0;
    virtual uint32_t get_height() const = 0;
    virtual void* get_native_window() const = 0;

    virtual void set_title(const std::string& title) = 0;
    virtual void set_cursor(bool locked) = 0;
  };
}