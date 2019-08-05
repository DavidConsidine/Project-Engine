#include "pepch.h"
#include "Shader.h"
#include "Core/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace ProjectEngine
{
	Shader* Shader::Create(const std::string& vertexSrc, std::string& fragmentSrc)
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
			return new OpenGLShader(vertexSrc, fragmentSrc);
		}
		}

		PE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}