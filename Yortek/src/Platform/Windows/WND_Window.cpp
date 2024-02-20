#include "Platform/Windows/WND_Window.h"

#include <GLFW/glfw3.h>

namespace Yortek::WND
{
  WND_Window::WND_Window(const Builder& builder)
  {
		if (int glfw = glfwInit(); !glfw)
		{
			//Log::critical("Failed to init GLFW");
			return;
		}

		if (m_window = glfwCreateWindow(builder.width, builder.height, builder.title.c_str(), nullptr, nullptr); !m_window)
		{
			//Log::critical("Failed to create GLFW window!");
			return;
		}

		glfwMakeContextCurrent(m_window);
		m_graphics_context = GraphicsContext::Builder()
			.set_window_handle(m_window)
			.build();

		glfwSwapInterval((int)builder.vsync);
		glfwSetWindowUserPointer(m_window, this);

		if (builder.fixed_aspect_ratio)
			glfwSetWindowAspectRatio(m_window, builder.width, builder.height);

		// Setup Callbacks GLFW

		glfwSetErrorCallback([](int error, const char* desc)
			{
				//Log::error(desc);
			});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
			{
				WND_Window* wWindow = ((WND_Window*)glfwGetWindowUserPointer(window));
				wWindow->OnWindowClose.dispatch();
			});

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
			{
				WND_Window* wWindow = ((WND_Window*)glfwGetWindowUserPointer(window));
				wWindow->m_builder.width = width;
				wWindow->m_builder.height = height;

				wWindow->OnWindowResize.dispatch(width, height);
			});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WND_Window* wWindow = ((WND_Window*)glfwGetWindowUserPointer(window));
				if (action == GLFW_PRESS)
					wWindow->OnKeyPressed.dispatch(key);
				else if (action == GLFW_RELEASE)
					wWindow->OnKeyReleased.dispatch(key);
			});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos)
			{
				WND_Window* wWindow = ((WND_Window*)glfwGetWindowUserPointer(window));
				wWindow->OnMouseMoved.dispatch(xpos, ypos);
			});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				WND_Window* wWindow = ((WND_Window*)glfwGetWindowUserPointer(window));
				wWindow->OnMouseScrolled.dispatch((float)yoffset);
			});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WND_Window* wWindow = ((WND_Window*)glfwGetWindowUserPointer(window));
				if (action == GLFW_PRESS)
				{
					wWindow->OnMouseButtonPressed.dispatch(button);
				}
				else if (action == GLFW_RELEASE)
					wWindow->OnMouseButtonReleased.dispatch(button);
			});

		//Log::info("Window Created!");
  }

	WND_Window::~WND_Window()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

  void WND_Window::update()
  {
		glfwPollEvents();
		m_graphics_context->swap_buffers();
  }

  void WND_Window::set_title(const std::string& title)
  {
  }
  void WND_Window::set_cursor(bool locked)
  {
  }
}