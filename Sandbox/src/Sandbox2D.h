#pragma once

#include "ProjectEngine.h"

class Sandbox2D : public ProjectEngine::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(ProjectEngine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(ProjectEngine::Event& e) override;

private:
	ProjectEngine::OrthographicCameraController m_CameraController;

	// Temp
	ProjectEngine::Ref<ProjectEngine::VertexArray> m_SquareVA;
	ProjectEngine::Ref<ProjectEngine::Shader> m_FlatColorShader;

	ProjectEngine::Ref<ProjectEngine::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};