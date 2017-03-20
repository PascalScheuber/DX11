#pragma once
#include "Engine\DX11Engine.h"

class CubeRotator5000
{
#pragma region Variables
public:

private:

	Engine::DX11Window m_DX11Window;
	Engine::DX11Renderer m_DX11Renderer;
	Engine::PrimitiveType::Cube m_Cube;
	Engine::Camera m_Camera;
	Engine::PointLight m_PointLight;
	Engine::AmbientLight m_AmbientLight;
	Engine::Timer m_Timer;

	MSG m_Message;

	Shader::S_VSConstantBufferData m_VSData;
	Shader::S_PSConstantBufferData m_PSData;

	float m_CurrentTime = 0;
	float m_ClearColor[3] = { 0.5f, 0.5f, 0.5f };

	double m_FixedDeltaTime = 0;
	float m_FixedRotationAngle = 0;

	bool m_Quit = false;

#pragma endregion

#pragma region Methods
public:
	CubeRotator5000();
	~CubeRotator5000();

	void Update();

	bool GetQuit();

private:
	void FixedUpdate();
	void Render(bool a_RenderDebug);

	void FillShaderData();
	void UpdateShaderData();

#pragma endregion
};
