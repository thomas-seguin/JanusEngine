#include "Sandbox2D.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {

}

void Sandbox2D::OnAttach() {

	m_CheckerboardTexture = Janus::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach() {
}

void Sandbox2D::OnUpdate(Janus::Timestep ts) {
	JN_PROFILE_FUNCTION();

	// Update
	{
		JN_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}


	// Render
	{
		JN_PROFILE_SCOPE("Renderer Prep");
		Janus::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Janus::RenderCommand::Clear();
	}

	{
		JN_PROFILE_SCOPE("Renderer Draw");

		Janus::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Janus::Renderer2D::DrawQuad({ -1.0f,0.0f }, { 0.8f, 0.8f }, { 0.8f,0.2f, 0.3f, 1.0f });
		Janus::Renderer2D::DrawQuad({ 0.5f,-0.5f }, { 0.5f, 0.75f }, { 0.2f,0.3f, 0.8f, 1.0f });
		Janus::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f, glm::vec4(1.0f, 0.9f, 0.9f, 1.0f));
		Janus::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, 45.0f, m_CheckerboardTexture,  20.0f);
		Janus::Renderer2D::EndScene();

		Janus::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f) {
			for (float x = -5.0f; x < 5.0f; x += 0.5f) {
				glm::vec4 color = { (x + 5.0) / 10.0, 0.4f, (y + 5.0f) / 10.0f, 1.0f };
				Janus::Renderer2D::DrawQuad({x,y}, { 0.45f, 0.45f }, color);

			}
		}
		Janus::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender() {
	JN_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = Janus::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats: ");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(Janus::Event& e) {
	m_CameraController.OnEvent(e);
}