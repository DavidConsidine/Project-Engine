#include "pepch.h"
#include "VertexArray.h"
#include "Core/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace ProjectEngine
{
	VertexArray * VertexArray::Create()
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
			return new OpenGLVertexArray();
		}
		}

		PE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}