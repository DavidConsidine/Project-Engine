#pragma once
#include "Core/Renderer/RendererAPI.h"

namespace ProjectEngine
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearClear(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}