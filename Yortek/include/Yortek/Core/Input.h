#pragma once

#include "Yortek/Core/KeyCodes.h"
#include "Yortek/Core/Event.h"
#include "Yortek/Tools/Singleton.h"

namespace Yortek
{
  class Input : public Tools::Singleton<Input, true>
  {
  public:
    Input();

    static Event<KeyCode> ev_OnKeyPressed;
    static Event<KeyCode> ev_OnKeyReleased;

    static bool is_key_pressed(KeyCode key);
    static void set_cursor(bool locked);

  private:
    static void _on_key_pressed(int key);
    static void _on_key_released(int key);
    static void _on_mouse_button_pressed(int button);
    static void _on_mouse_button_released(int button);

  private:
    static bool s_keys[512];
  };
}