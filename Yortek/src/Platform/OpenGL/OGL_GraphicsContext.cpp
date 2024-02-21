#include "Platform/OpenGL/OGL_GraphicsContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Yortek::Rendering::OGL
{
  OGL_GraphicsContext::OGL_GraphicsContext(const Builder& builder)
    : m_builder(builder)
  {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      // TODO: log error
    }
  }

  void OGL_GraphicsContext::swap_buffers()
  {
    glfwSwapBuffers(static_cast<GLFWwindow*>(m_builder.window_handle));
  }
}