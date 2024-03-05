#include "Yortek/Rendering/CameraInfo.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Yortek::Rendering
{
  CameraInfo::CameraInfo()
  {
    m_framebuffer = Framebuffer::Builder()
      .set_size({ 200, 200 })
      .build();

    resize(200, 200);
  }

  void CameraInfo::resize(int width, int height)
  {
    if (width <= 0 || height <= 0) return;

    IVector2 newSize = IVector2(width, height);
    if (newSize == m_current_size) return;

    float aspect = float(width) / float(height);

    if (mode == CameraMode::Perspective)
    {
      m_projection = glm::perspective(glm::radians(field_of_view), aspect, near_clip, far_clip);
    }
    else
    {
      m_projection = glm::ortho(-ortho_size * aspect, ortho_size * aspect, -ortho_size, ortho_size, near_clip, far_clip);
    }

    m_current_size = newSize;
    m_framebuffer->resize(newSize);
  }
}