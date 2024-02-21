#include "Yortek/Core/Input.h"
#include "Yortek/Core/Application.h"

namespace Yortek
{
  Event<KeyCode> Input::ev_OnKeyPressed;
  Event<KeyCode> Input::ev_OnKeyReleased;
  bool Input::s_keys[512]{};

  Input::Input()
  {
    Application::get_window()->ev_OnKeyPressed += _on_key_pressed;
    Application::get_window()->ev_OnKeyReleased += _on_key_released;
    Application::get_window()->ev_OnMouseButtonPressed += _on_mouse_button_pressed;
    Application::get_window()->ev_OnMouseButtonReleased += _on_mouse_button_released;
  }

  bool Input::is_key_pressed(KeyCode key)
  {
    instance();
    return s_keys[(_Key)key];
  }

  void Input::set_cursor(bool locked)
  {
    Application::get_window()->set_cursor(locked);
  }

  void Input::_on_key_pressed(int key)
  {
    s_keys[key] = true;
    ev_OnKeyPressed.dispatch((KeyCode)key);
  }

  void Input::_on_key_released(int key)
  {
    s_keys[key] = false;
    ev_OnKeyReleased.dispatch((KeyCode)key);
  }

  void Input::_on_mouse_button_pressed(int button)
  {
    switch (button)
    {
    case 0: s_keys[(_Key)KeyCode::LeftMouseButton] = true; break;
    case 1: s_keys[(_Key)KeyCode::RightMouseButton] = true; break;
    case 2: s_keys[(_Key)KeyCode::MiddleMouseButton] = true; break;
    }
  }

  void Input::_on_mouse_button_released(int button)
  {
    switch (button)
    {
    case 0: s_keys[(_Key)KeyCode::LeftMouseButton] = false; break;
    case 1: s_keys[(_Key)KeyCode::RightMouseButton] = false; break;
    case 2: s_keys[(_Key)KeyCode::MiddleMouseButton] = false; break;
    }
  }
}