#include "pepch.h"

#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace ProjectEngine
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}