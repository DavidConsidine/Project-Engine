#include <ProjectEngine.h>

#include "imgui/imgui.h"

class ExampleLayer : public ProjectEngine::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(ProjectEngine::VertexArray::Create());

		float vertices[3 * 7] = {
				-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
				 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
				 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		std::shared_ptr<ProjectEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(ProjectEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
		ProjectEngine::BufferLayout layout = {
			{ ProjectEngine::ShaderDataType::Float3, "a_Position" },
			{ ProjectEngine::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		std::shared_ptr<ProjectEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(ProjectEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(ProjectEngine::VertexArray::Create());

		float squareVertices[3 * 4] = {
				-0.75f, -0.75f, 0.0f,
				 0.75f, -0.75f, 0.0f,
				 0.75f,  0.75f, 0.0f,
				-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<ProjectEngine::VertexBuffer> squarevertexBuffer;
		squarevertexBuffer.reset(ProjectEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squarevertexBuffer->SetLayout({
				{ProjectEngine::ShaderDataType::Float3, "a_Position"}
			});
		m_SquareVA->AddVertexBuffer(squarevertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<ProjectEngine::IndexBuffer> squareindexBuffer;
		squareindexBuffer.reset(ProjectEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices)));
		m_SquareVA->SetIndexBuffer(squareindexBuffer);


		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;
			
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new ProjectEngine::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new ProjectEngine::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate(ProjectEngine::Timestep ts) override
	{
		if (ProjectEngine::Input::IsKeyPressed(PE_KEY_LEFT))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		}
		else if (ProjectEngine::Input::IsKeyPressed(PE_KEY_RIGHT))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		}
		if (ProjectEngine::Input::IsKeyPressed(PE_KEY_UP))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		}
		else if (ProjectEngine::Input::IsKeyPressed(PE_KEY_DOWN))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		}

		if (ProjectEngine::Input::IsKeyPressed(PE_KEY_A))
		{
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}
		if (ProjectEngine::Input::IsKeyPressed(PE_KEY_D))
		{
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}

		ProjectEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		ProjectEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		ProjectEngine::Renderer::BeginScene(m_Camera);

		ProjectEngine::Renderer::Submit(m_BlueShader, m_SquareVA);
		ProjectEngine::Renderer::Submit(m_Shader, m_VertexArray);

		ProjectEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender()
	{
	}

	void OnEvent(ProjectEngine::Event& event) override
	{
	}

private:
	std::shared_ptr<ProjectEngine::Shader> m_Shader;
	std::shared_ptr<ProjectEngine::VertexArray> m_VertexArray;

	std::shared_ptr<ProjectEngine::Shader> m_BlueShader;
	std::shared_ptr<ProjectEngine::VertexArray> m_SquareVA;

	ProjectEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;
};



class Sandbox : public ProjectEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};


ProjectEngine::Application* ProjectEngine::CreateApplication()
{
	return new Sandbox();
}