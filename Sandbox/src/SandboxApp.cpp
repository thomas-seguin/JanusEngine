#include "Janus.h"

class ExampleLayer : public Janus::Layer {
public:
	ExampleLayer() : Layer("Example") {
	}

	void OnUpdate() override {
		JN_INFO("ExampleLayer::Update");
	}

	void OnEvent(Janus::Event& event) override {
		JN_INFO("{0}", event.ToString());
	}
};

class Sandbox : public Janus::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

Janus::Application* Janus::CreateApplication() {
	return new Sandbox();
}