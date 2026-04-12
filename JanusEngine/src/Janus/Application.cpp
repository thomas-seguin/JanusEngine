#include "jnpch.h"
#include "Application.h"

#include "Janus/Log.h"
#include "Janus/Events/ApplicationEvent.h"


namespace Janus {
	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}
	Application::~Application() {
	}

	void Application::Run() {

		while (m_Running) {
			m_Window->OnUpdate();
		}
	}
}
