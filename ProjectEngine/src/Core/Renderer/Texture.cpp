#include "pepch.h"
#include "Texture.h"

#include "Core/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace ProjectEngine
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				PE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return std::make_shared<OpenGLTexture2D>(path);
			}
		}

		PE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}