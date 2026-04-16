#include "jnpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Janus {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) 
		: m_WindowHandle(windowHandle) {}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		JN_CORE_ASSERT(status, "Failed to initialize Glad!");

		JN_CORE_INFO("OpenGL Info: ");
		JN_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		JN_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		JN_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));

	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}
}