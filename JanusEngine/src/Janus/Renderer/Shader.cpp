#include "jnpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Janus {
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			JN_CORE_ASSERT(false, "RendererAPI::None is current not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		return nullptr;
	}
}