#include "Janus.h"


#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ExampleLayer : public Janus::Layer {
public:
	ExampleLayer() : Layer("Example"), m_CameraController(1280.0f / 720.0f) {
		m_VertexArray.reset(Janus::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 1.0f, 0.0, 1.0f, 1.0f
		};

		Janus::Ref<Janus::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Janus::VertexBuffer::Create(vertices, sizeof(vertices)));
		Janus::BufferLayout layout = {
			{Janus::ShaderDataType::Float3, "a_Position"},
			{Janus::ShaderDataType::Float4, "a_Color"},
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Janus::Ref<Janus::IndexBuffer> indexBuffer;
		indexBuffer.reset(Janus::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Janus::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f

		};
		Janus::Ref<Janus::VertexBuffer> sqaureVB;
		sqaureVB.reset(Janus::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		sqaureVB->SetLayout({
			{Janus::ShaderDataType::Float3, "a_Position"},
			{Janus::ShaderDataType::Float2, "a_TexCoord"}
			});
		m_SquareVA->AddVertexBuffer(sqaureVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Janus::Ref<Janus::IndexBuffer> sqaureIB;
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

		m_Shader = Janus::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
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

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main() 
			{
				color = vec4(u_Color,1.0);
			}
		)";

		m_FlatColorShader = Janus::Shader::Create("FlatColor",flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Janus::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = Janus::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Janus::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Janus::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Janus::Timestep ts) override {
		// Update
		m_CameraController.OnUpdate(ts);

		// Render
		Janus::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Janus::RenderCommand::Clear();

		Janus::Renderer::BeginScene(m_CameraController.GetCamera());

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Janus::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Janus::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);


		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Janus::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Janus::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.51f)));

		m_ChernoLogoTexture->Bind();
		Janus::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.51f)));

		//Janus::Renderer::Submit(m_Shader, m_VertexArray);

		Janus::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Janus::Event& e) override {
		m_CameraController.OnEvent(e);
	}

private:
	Janus::ShaderLibrary m_ShaderLibrary;
	Janus::Ref<Janus::Shader> m_Shader;
	Janus::Ref<Janus::VertexArray> m_VertexArray;

	Janus::Ref<Janus::Shader> m_FlatColorShader;
	Janus::Ref<Janus::VertexArray> m_SquareVA;

	Janus::Ref<Janus::Texture2D> m_Texture, m_ChernoLogoTexture;

	Janus::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f,0.3f,0.8f };
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