#include "Sandbox2D.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {

}

void Sandbox2D::OnAttach() {

	m_SquareVA = Janus::VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};
	Janus::Ref<Janus::VertexBuffer> sqaureVB;
	sqaureVB.reset(Janus::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	sqaureVB->SetLayout({
		{Janus::ShaderDataType::Float3, "a_Position"}
		});
	m_SquareVA->AddVertexBuffer(sqaureVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Janus::Ref<Janus::IndexBuffer> sqaureIB;
	sqaureIB.reset(Janus::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVA->SetIndexBuffer(sqaureIB);

	m_FlatColorShader = Janus::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach() {
}

void Sandbox2D::OnUpdate(Janus::Timestep ts) {
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Janus::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Janus::RenderCommand::Clear();

	Janus::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Janus::Renderer2D::DrawQuad({ -1.0f,0.0f }, { 0.8f, 0.8f }, { 0.8f,0.2f, 0.3f, 1.0f });
	Janus::Renderer2D::DrawQuad({ 0.5f,-0.5f }, { 0.5f, 0.75f }, { 0.2f,0.3f, 0.8f, 1.0f });

	Janus::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Janus::Event& e) {
	m_CameraController.OnEvent(e);
}