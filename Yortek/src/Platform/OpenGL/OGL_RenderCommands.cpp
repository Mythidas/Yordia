#include "Platform/OpenGL/OGL_RenderCommands.h"

#include <glad/glad.h>

namespace Yortek::Rendering::OGL
{
  void OGL_RenderCommands::_enable_depth_testing_impl(bool enable)
  {
    if (enable) glEnable(GL_DEPTH_TEST);
    else glDisable(GL_DEPTH_TEST);
  }

  void OGL::OGL_RenderCommands::_enable_blending_impl(bool enable)
  {
    if (enable)
    {
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    else
    {
      glDisable(GL_BLEND);
    }
  }

  void OGL_RenderCommands::_clear_color_impl(float r, float g, float b)
  {
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void OGL_RenderCommands::_resize_impl(int width, int height)
  {
    if (width <= 0 || height <= 0) return;
    glViewport(0, 0, width, height);
  }
}