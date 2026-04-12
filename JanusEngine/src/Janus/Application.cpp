#include "jnpch.h"
#include "Application.h"

#include "Janus/Log.h"
#include "Janus/Events/ApplicationEvent.h"


namespace Janus {
	Application::Application() {

	}
	Application::~Application() {
	}

	void Application::Run() {
		WindowResizeEvent e(1280, 720);
		JN_TRACE(e.ToString());

		while (true);
	}
}
