#include "pepch.h"

#include "Core/Renderer/RenderCommand.h"

namespace ProjectEngine
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}