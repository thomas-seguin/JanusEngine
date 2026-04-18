#include "jnpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Janus {
	Ref<Texture2D> Texture2D::Create(const std::string& path){
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			JN_CORE_ASSERT(false, "RendererAPI::None is current not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		}

		return nullptr;
	}
}