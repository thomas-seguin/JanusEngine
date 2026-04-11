#pragma once

#ifdef JN_PLATFORM_WINDOWS

extern Janus::Application* Janus::CreateApplication();

int main(int argc, char** argv) {
	auto app = Janus::CreateApplication();
	app->Run();
	delete app;
}

#endif