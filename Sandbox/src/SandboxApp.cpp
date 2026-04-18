#include "Janus.h"

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Janus::Layer {
public:
	ExampleLayer() : Layer("Example"), m_Camera(-1.0f, 1.0f, -1.0f, 1.0f), m_CameraPosition(0.0f,0.0f,0.0f), m_SquarePosition(0.0f) {
		m_VertexArray.reset(Janus::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 1.0f, 0.0, 1.0f, 1.0f
		};

		std::shared_ptr<Janus::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Janus::VertexBuffer::Create(vertices, sizeof(vertices)));
		Janus::BufferLayout layout = {
			{Janus::ShaderDataType::Float3, "a_Position"},
			{Janus::ShaderDataType::Float4, "a_Color"},
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Janus::IndexBuffer> indexBuffer;
		indexBuffer.reset(Janus::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Janus::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f

		};
		std::shared_ptr<Janus::VertexBuffer> sqaureVB;
		sqaureVB.reset(Janus::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		sqaureVB->SetLayout({
			{Janus::ShaderDataType::Float3, "a_Position"}
			});
		m_SquareVA->AddVertexBuffer(sqaureVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Janus::IndexBuffer> sqaureIB;
		sqaureIB.reset(Janus::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(sqaureIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() 
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main() 
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Janus::Shader(vertexSrc, fragmentSrc));

		std::string vertexSrc2 = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main() 
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc2 = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main() 
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		m_Shader2.reset(new Janus::Shader(vertexSrc2, fragmentSrc2));
	}

	void OnUpdate(Janus::Timestep ts) override {

		if (Janus::Input::IsKeyPressed(JN_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;

		else if (Janus::Input::IsKeyPressed(JN_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Janus::Input::IsKeyPressed(JN_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		else if (Janus::Input::IsKeyPressed(JN_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;

		if (Janus::Input::IsKeyPressed(JN_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Janus::Input::IsKeyPressed(JN_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		if (Janus::Input::IsKeyPressed(JN_KEY_J))
			m_SquarePosition.x -= m_SquareMoveSpeed * ts;

		else if (Janus::Input::IsKeyPressed(JN_KEY_L))
			m_SquarePosition.x += m_SquareMoveSpeed * ts;

		if (Janus::Input::IsKeyPressed(JN_KEY_K))
			m_SquarePosition.y -= m_SquareMoveSpeed * ts;

		else if (Janus::Input::IsKeyPressed(JN_KEY_I))
			m_SquarePosition.y += m_SquareMoveSpeed * ts;


		Janus::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Janus::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Janus::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Janus::Renderer::Submit(m_Shader2, m_SquareVA, transform);
			}
		}

		//Janus::Renderer::Submit(m_Shader, m_VertexArray);

		Janus::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {

	}

	void OnEvent(Janus::Event& event) override {
	}

private:
	std::shared_ptr<Janus::Shader> m_Shader;
	std::shared_ptr<Janus::VertexArray> m_VertexArray;

	std::shared_ptr<Janus::Shader> m_Shader2;
	std::shared_ptr<Janus::VertexArray> m_SquareVA;

	Janus::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquarePosition;
	float m_SquareMoveSpeed = 1.0f;

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