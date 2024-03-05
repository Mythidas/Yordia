#pragma once

#include "Yortek/Core/Defines.h"
#include "Yortek/Rendering/Framebuffer.h"
#include "Yortek/Rendering/Color.h"
#include "Yortek/Math/include.h"

namespace Yortek::Rendering
{
  using namespace Math;

  enum class CameraMode
  {
    Perspective,
    Orthographic
  };

  struct CameraInfo
  {
  public:
    CameraInfo();

    Color clear_color{ 1.0f, 1.0f, 1.0f, 1.0f };
    CameraMode mode{ CameraMode::Perspective };
    float field_of_view{ 60.0f };
    float near_clip{ 0.01f };
    float far_clip{ 100.0f };
    float ortho_size{ 10.0f };
    bool active{ false };

    void resize(int width, int height);

    Matrix4 get_projection() const { return m_projection; }
    Shared<Framebuffer> get_framebuffer() const { return m_framebuffer; }
    
  private:
    Matrix4 m_projection;
    Shared<Framebuffer> m_framebuffer;
    IVector2 m_current_size;
  };
}