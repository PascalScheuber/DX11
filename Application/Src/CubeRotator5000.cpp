#include "CubeRotator5000.h"

CubeRotator5000::CubeRotator5000()
{
	//---------------------------------------------------------------
	//	DX11 Window
	//---------------------------------------------------------------

	Engine::S_DX11WindowDesc DX11WindowDesc;

	DX11WindowDesc.Resolution[0] = 1280;
	DX11WindowDesc.Resolution[1] = 720;
	DX11WindowDesc.Fullscreen = false;
	DX11WindowDesc.CmdShow = 1;

	m_DX11Window.Initialize(&DX11WindowDesc);

	//---------------------------------------------------------------
	//	DX11 Renderer
	//---------------------------------------------------------------

	Engine::S_DX11RendererDesc DX11RendererDesc;
	DX11RendererDesc.RenderType = Engine::E_RenderType::TriangleStrip;
	DX11RendererDesc.MaxVerticesPerRender = 24;
	DX11RendererDesc.FixedFPS = 60;

	m_DX11Renderer.Initialize(m_DX11Window.GetWindowDesc(), &DX11RendererDesc);

	//---------------------------------------------------------------
	//	Camera
	//---------------------------------------------------------------

	Engine::S_CameraDesc CameraDesc;
	CameraDesc.Resolution[0] = DX11WindowDesc.Resolution[0];
	CameraDesc.Resolution[1] = DX11WindowDesc.Resolution[1];
	CameraDesc.FoV = 80;
	CameraDesc.NearPlane = 0.01f;
	CameraDesc.FarPlane = 1000.0f;
		
	m_Camera.Initialize(&CameraDesc);
	m_Camera.SetPosition(DirectX::XMVECTOR{ 0.0f, 1.0f, -2.0f });
	
	//---------------------------------------------------------------
	//	PointLight
	//---------------------------------------------------------------

	m_PointLight.SetPosition(DirectX::XMVECTOR{ 0.0f, -0.5f, -2.0f });
	m_PointLight.SetLightColor(DirectX::XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f });
	m_PointLight.SetLightRadius(10.0f);
	m_PointLight.SetLightIntensity(1.0f);

	//---------------------------------------------------------------
	//	AmbientLight
	//---------------------------------------------------------------

	m_AmbientLight.SetLightColor(DirectX::XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f });
	m_AmbientLight.SetLightIntensity(0.3f);

	//---------------------------------------------------------------
	//	Shader
	//---------------------------------------------------------------

	D3D11_INPUT_ELEMENT_DESC InputElementDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	m_DX11Renderer.LoadShader(Engine::E_ShaderType::VertexShader, InputElementDesc, ARRAYSIZE(InputElementDesc), L"Data\\Shader\\PhongShader.shader", "VS_Main", "vs_5_0");
	m_DX11Renderer.LoadShader(Engine::E_ShaderType::PixelShader, InputElementDesc, ARRAYSIZE(InputElementDesc), L"Data\\Shader\\PhongShader.shader", "PS_Main", "ps_5_0");

	FillShaderData();
	
	m_FixedDeltaTime = 1.0f / m_DX11Renderer.GetRendererDesc()->FixedFPS;

	m_FixedRotationAngle = 360.0f / (float)m_DX11Renderer.GetRendererDesc()->FixedFPS;
}

CubeRotator5000::~CubeRotator5000()
{
}

void CubeRotator5000::Update()
{
	m_Timer.Update();
	m_CurrentTime += (float)m_Timer.GetDeltaTime();

	if (m_CurrentTime > m_FixedDeltaTime)
	{
		m_CurrentTime -= (float)m_FixedDeltaTime;

		FixedUpdate();
		Render(true);
	}

	//Peek Window Message
	if (PeekMessage(&m_Message, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&m_Message);
		DispatchMessage(&m_Message);

		if (m_Message.message == WM_QUIT)
		{
			m_Quit = true;
		}
	}
}

bool CubeRotator5000::GetQuit()
{
	return m_Quit;
}

void CubeRotator5000::FixedUpdate()
{
	m_Cube.Rotate(DirectX::XMVECTOR{ 0, 1, 0 }, DirectX::XMVECTOR{ 0.0f, m_FixedRotationAngle, 0.0f });

	UpdateShaderData();
}

void CubeRotator5000::Render(bool a_RenderDebug)
{
	m_DX11Renderer.Begin(m_ClearColor);

	if (a_RenderDebug)
	{
		for (int i = 0; i < (int)m_Cube.GetDebugVertices().size(); i++)
		{
			m_DX11Renderer.Render(m_Cube.GetDebugVertices()[i], Engine::E_RenderType::TriangleStrip);
		}
	}
	else
	{
		m_DX11Renderer.Render(m_Cube.GetVertices(), Engine::E_RenderType::TriangleStrip);
	}


	m_DX11Renderer.End();
}

void CubeRotator5000::FillShaderData()
{
	//---------------------------------------------------------------
	//	Fill VS Data
	//---------------------------------------------------------------

	m_VSData.World = m_Cube.GetWorldMatrix();
	m_VSData.View = DirectX::XMMatrixTranspose(m_Camera.GetViewMatrix());
	m_VSData.Projection = DirectX::XMMatrixTranspose(m_Camera.GetProjectionMatrix());

	//---------------------------------------------------------------
	//	Fill PS Data
	//---------------------------------------------------------------

	m_PSData.ViewDirection[0] = m_Camera.GetLookDirection().m128_f32[0];
	m_PSData.ViewDirection[1] = m_Camera.GetLookDirection().m128_f32[1];
	m_PSData.ViewDirection[2] = m_Camera.GetLookDirection().m128_f32[2];

	m_PSData.AmbientLightColor[0] = m_AmbientLight.GetLightColor().x;
	m_PSData.AmbientLightColor[1] = m_AmbientLight.GetLightColor().y;
	m_PSData.AmbientLightColor[2] = m_AmbientLight.GetLightColor().z;
	m_PSData.AmbientLightColor[3] = m_AmbientLight.GetLightColor().w;

	m_PSData.AmbientIntensity = m_AmbientLight.GetLightIntensity();

	m_PSData.LightColor[0] = m_PointLight.GetLightColor().x;
	m_PSData.LightColor[1] = m_PointLight.GetLightColor().y;
	m_PSData.LightColor[2] = m_PointLight.GetLightColor().z;
	m_PSData.LightColor[3] = m_PointLight.GetLightColor().w;

	m_PSData.LightIntensity = m_PointLight.GetLightIntensity();

	m_PSData.LightPosition[0] = m_PointLight.GetPosition().m128_f32[0];
	m_PSData.LightPosition[1] = m_PointLight.GetPosition().m128_f32[1];
	m_PSData.LightPosition[2] = m_PointLight.GetPosition().m128_f32[2];

	m_PSData.LightRadius = m_PointLight.GetLightRadius();

	m_DX11Renderer.FillVSShaderData(&m_VSData);
	m_DX11Renderer.FillPSShaderData(&m_PSData);
	
}

void CubeRotator5000::UpdateShaderData()
{
	m_VSData.World = m_Cube.GetWorldMatrix();

	m_DX11Renderer.FillVSShaderData(&m_VSData);
}
