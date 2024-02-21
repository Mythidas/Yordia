#include "YTEngine/Graphics/Camera.h"
#include "YTEngine/Core/Application.h"
#include "YTEngine/Scene/SceneView.h"
#include "YTEngine/Scene/Entity.h"
#include "YTEngine/Scene/Ref.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Yor
{
  Camera::Camera()
  {
    if (!Application::isRunning()) return;

    glm::uvec2 size(Application::getWindow()->getWidth(), Application::getWindow()->getHeight());
    m_swapBuffer = Framebuffer::Builder()
      .setSize(size)
      .build();
  }

  void Camera::resize(int width, int height)
  {
    if (width <= 0 || height <= 0) return;

    glm::uvec2 newSize = glm::uvec2(uint32_t(width), uint32_t(height));
    if (newSize == m_currentSize) return;

    float aspect = float(width) / float(height);

    if (mode == CameraMode::Perspective)
    {
      m_projection = glm::perspective(glm::radians(fieldOfView), aspect, nearClip, farClip);
    }
    else
    {
      m_projection = glm::ortho(-orthoSize * aspect, orthoSize * aspect, -orthoSize, orthoSize, nearClip, farClip);
    }

    m_currentSize = newSize;
    m_swapBuffer->resize(newSize);
  }

  Ref<Camera> Camera::getActiveCamera()
  {
    for (Entity ent : SceneView<Camera>())
    {
      Camera* camera = ent.getComponent<Camera>();
      if (camera && camera->active)
        return Ref<Camera>(ent);
    }

    return nullptr;
  }
}