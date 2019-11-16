#include "Sandbox2D.h"

#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_SquareVA = ProjectEngine::VertexArray::Create();

	float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
	};

	ProjectEngine::Ref<ProjectEngine::VertexBuffer> squarevertexBuffer;
	squarevertexBuffer.reset(ProjectEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squarevertexBuffer->SetLayout({
			{ProjectEngine::ShaderDataType::Float3, "a_Position"}
		});
	m_SquareVA->AddVertexBuffer(squarevertexBuffer);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	ProjectEngine::Ref<ProjectEngine::IndexBuffer> squareindexBuffer;
	squareindexBuffer.reset(ProjectEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices)));
	m_SquareVA->SetIndexBuffer(squareindexBuffer);

	m_FlatColorShader = ProjectEngine::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(ProjectEngine::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	ProjectEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	ProjectEngine::RenderCommand::Clear();

	ProjectEngine::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<ProjectEngine::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<ProjectEngine::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	ProjectEngine::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	ProjectEngine::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(ProjectEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}
