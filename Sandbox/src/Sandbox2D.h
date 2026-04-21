#pragma once

#include "Janus.h"

class Sandbox2D : public Janus::Layer {
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Janus::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Janus::Event& e) override;
private:
	Janus::OrthographicCameraController m_CameraController;

	Janus::Ref<Janus::VertexArray> m_SquareVA;
	Janus::Ref<Janus::Shader> m_FlatColorShader;

	Janus::Ref<Janus::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f,0.3f,0.8f, 1.0f };
};