#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = ProjectEngine::Texture2D::Create("assets/textures/checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(ProjectEngine::Timestep ts)
{
	PE_PROFILE_FUNCTION();
	// Update
	{
		PE_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	// Render
	{
		PE_PROFILE_SCOPE("Renderer Prep");
		ProjectEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		ProjectEngine::RenderCommand::Clear();
	}
	{
		PE_PROFILE_SCOPE("Renderer Draw");
		ProjectEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
		ProjectEngine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		ProjectEngine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.2f, 0.8f, 1.0f });
		ProjectEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
		ProjectEngine::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	PE_PROFILE_FUNCTION();
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(ProjectEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}
