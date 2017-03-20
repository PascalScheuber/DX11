#include "DX11Renderer.h"

Engine::DX11Renderer::DX11Renderer()
{
}

Engine::DX11Renderer::~DX11Renderer()
{
}

int Engine::DX11Renderer::Initialize(Engine::S_DX11WindowDesc* a_DX11WindowDesc, Engine::S_DX11RendererDesc* a_DX11RendererDesc)
{
	int result = 0;

	m_DX11RendererDesc = *a_DX11RendererDesc;

	if (result = InitializeDirectX11(a_DX11WindowDesc, &m_DX11RendererDesc) > 0)
	{
		if(result = InitializeDefaultShader(m_DX11RendererDesc.ShaderPath, m_DX11RendererDesc.MaxVerticesPerRender) < 0)
			return result;
	}
	else
		return result;

	return 1;	//Return True
}

Engine::S_DX11RendererDesc* Engine::DX11Renderer::GetRendererDesc()
{
	return &m_DX11RendererDesc;
}

void Engine::DX11Renderer::Begin(float a_clearColor[4])
{
	//---------------------------------------------------------------
	//	Clear
	//---------------------------------------------------------------

	m_pContext->ClearRenderTargetView(m_pBackBufferView, a_clearColor);
	m_pContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);	
}

void Engine::DX11Renderer::Render(std::vector<Shader::S_Vertex> a_Vertices, Engine::E_RenderType a_RenderType)
{
	//---------------------------------------------------------------
	//	Copy Vertex Data
	//---------------------------------------------------------------

	m_pContext->Map(m_pVertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &m_MappedSubResource);
	memcpy(m_MappedSubResource.pData, &a_Vertices.front(), sizeof(Shader::S_Vertex) * a_Vertices.size());
	m_pContext->Unmap(m_pVertexBuffer, NULL);

	//---------------------------------------------------------------
	//	Render
	//---------------------------------------------------------------

	switch (a_RenderType)
	{
	case Engine::E_RenderType::TriangleList:
		m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	case Engine::E_RenderType::TriangleStrip:
		m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		break;
	}

	m_pContext->Draw((UINT)a_Vertices.size(), 0);
}

void Engine::DX11Renderer::End()
{
	//---------------------------------------------------------------
	//	Swap Buffers
	//---------------------------------------------------------------

	m_pSwapChain->Present(0, 0);
}

int Engine::DX11Renderer::LoadShader(Engine::E_ShaderType a_ShaderType, D3D11_INPUT_ELEMENT_DESC* a_InputElementDesc, UINT a_InputElementArraySize, LPCWSTR a_ShaderPath, char* a_ShaderEntryPoint, char* a_ShaderModel)
{
	switch (a_ShaderType)
	{
	case Engine::E_ShaderType::None:
	{
		return 0;	//No Shader Loaded
	}
	break;

	case Engine::E_ShaderType::VertexShader:
	{
		//---------------------------------------------------------------
		//	Create Initialize Types
		//---------------------------------------------------------------

		ID3D11VertexShader* pVS = nullptr;
		ID3DBlob* pVSBlob = nullptr;
		ID3D11InputLayout* pLayout = nullptr;

		//---------------------------------------------------------------
		//	Create VS Constant Buffer
		//---------------------------------------------------------------

		InitializeVSConstantBuffer();

		//---------------------------------------------------------------
		//	Load, Create and Set Shader
		//---------------------------------------------------------------

		D3DCompileFromFile(a_ShaderPath, 0, 0, a_ShaderEntryPoint, a_ShaderModel, 0, 0, &pVSBlob, 0);

		if (m_pDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &pVS) != S_OK)
		{
			return -1;
		}
		m_pContext->VSSetShader(pVS, NULL, 0);

		//---------------------------------------------------------------
		//	Set Shader InputLayout
		//---------------------------------------------------------------

		if(m_pDevice->CreateInputLayout(a_InputElementDesc, a_InputElementArraySize, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &pLayout) != S_OK)
		{
			return -2;
		}
		m_pContext->IASetInputLayout(pLayout);

		//---------------------------------------------------------------
		//	Release
		//---------------------------------------------------------------
		if (pVS != nullptr)
		{
			pVS->Release();
			pVS = nullptr;
		}

		if (pVSBlob != nullptr)
		{
			pVSBlob->Release();
			pVSBlob = nullptr;
		}

		if (pLayout != nullptr)
		{
			pLayout->Release();
			pLayout = nullptr;
		}
	}
	break;
	case Engine::E_ShaderType::PixelShader:
	{
		//---------------------------------------------------------------
		//	Create Initialize Types
		//---------------------------------------------------------------

		ID3D11PixelShader* pPS = nullptr;
		ID3DBlob* pPSBlob = nullptr;
		ID3D11InputLayout* pLayout = nullptr;
		
		//---------------------------------------------------------------
		//	Create PS Constant Buffer
		//---------------------------------------------------------------

		InitializePSConstantBuffer();

		//---------------------------------------------------------------
		//	Load, Create and Set Shader
		//---------------------------------------------------------------

		D3DCompileFromFile(a_ShaderPath, 0, 0, a_ShaderEntryPoint, a_ShaderModel, 0, 0, &pPSBlob, 0);

		if(m_pDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &pPS) != S_OK)
		{
			return -3;
		}

		m_pContext->PSSetShader(pPS, NULL, 0);

		//---------------------------------------------------------------
		//	Set Shader InputLayout
		//---------------------------------------------------------------

		if(m_pDevice->CreateInputLayout(a_InputElementDesc, a_InputElementArraySize, pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), &pLayout) != S_OK)
		{
			return -4;
		}
		m_pContext->IASetInputLayout(pLayout);

		//---------------------------------------------------------------
		//	Release
		//---------------------------------------------------------------
		if (pPS != nullptr)
		{
			pPS->Release();
			pPS = nullptr;
		}

		if (pPSBlob != nullptr)
		{
			pPSBlob->Release();
			pPSBlob = nullptr;
		}

		if (pLayout != nullptr)
		{
			pLayout->Release();
			pLayout = nullptr;
		}

	}
	break;
	}


	return 1;	//Return True
}

void Engine::DX11Renderer::FillVSShaderData(Shader::S_VSConstantBufferData* a_ShaderData)
{
	memcpy(m_pVSConstantBufferData, a_ShaderData, sizeof(Shader::S_VSConstantBufferData));
}

void Engine::DX11Renderer::FillPSShaderData(Shader::S_PSConstantBufferData* a_ShaderData)
{
	memcpy(m_pPSConstantBufferData, a_ShaderData, sizeof(Shader::S_PSConstantBufferData));
}

int Engine::DX11Renderer::InitializeDirectX11(Engine::S_DX11WindowDesc * a_DX11WindowDesc, Engine::S_DX11RendererDesc* a_DX11RendererDesc)
{
	//---------------------------------------------------------------
	//	Create Initialize Types
	//---------------------------------------------------------------

	ID3D11Texture2D* pBackBuffer			= nullptr;
	ID3D11Texture2D* pDepthStencilBuffer	= nullptr;
	DXGI_SWAP_CHAIN_DESC swapChainDesc		= { 0 };
	D3D11_TEXTURE2D_DESC depthStencilDesc	= { 0 };
	D3D11_VIEWPORT viewPort					= { 0 };
	D3D_FEATURE_LEVEL level					= D3D_FEATURE_LEVEL_11_0;


	//---------------------------------------------------------------
	//	Fill Swap Chain Description
	//---------------------------------------------------------------

	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = a_DX11WindowDesc->Hwnd;
	swapChainDesc.Windowed = !a_DX11WindowDesc->Fullscreen;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.Width = a_DX11WindowDesc->Resolution[0];
	swapChainDesc.BufferDesc.Height = a_DX11WindowDesc->Resolution[1];
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	//---------------------------------------------------------------
	//	Create Swap Chain and Device
	//---------------------------------------------------------------

	if(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL,
		NULL, D3D11_SDK_VERSION, &swapChainDesc, &m_pSwapChain, &m_pDevice, &level, &m_pContext) != S_OK)
	{
		return -5;
	}

	//---------------------------------------------------------------
	//	Get BackBuffer and Create RenderTargetView
	//---------------------------------------------------------------

	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if(m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pBackBufferView) != S_OK)
	{
		return -6;
	}

	//---------------------------------------------------------------
	//	Fill Depth Stencil Description
	//---------------------------------------------------------------

	ZeroMemory(&depthStencilDesc, sizeof(D3D11_TEXTURE2D_DESC));
	depthStencilDesc.Width = a_DX11WindowDesc->Resolution[0];
	depthStencilDesc.Height = a_DX11WindowDesc->Resolution[1];
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;

	//---------------------------------------------------------------
	//	Create DepthStencil Buffer and View. Set RenderTarget
	//---------------------------------------------------------------

	m_pDevice->CreateTexture2D(&depthStencilDesc, NULL, &pDepthStencilBuffer);
	if(m_pDevice->CreateDepthStencilView(pDepthStencilBuffer, NULL, &m_pDepthStencilView) != S_OK)
	{
		return -7;
	}

	m_pContext->OMSetRenderTargets(1, &m_pBackBufferView, m_pDepthStencilView);

	//---------------------------------------------------------------
	//	Fill and Set ViewPort
	//---------------------------------------------------------------

	viewPort.Width = (float)a_DX11WindowDesc->Resolution[0];
	viewPort.Height = (float)a_DX11WindowDesc->Resolution[1];
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;

	m_pContext->RSSetViewports(1, &viewPort);

	//---------------------------------------------------------------
	//	Release
	//---------------------------------------------------------------

	pBackBuffer->Release();
	pBackBuffer = nullptr;

	pDepthStencilBuffer->Release();
	pDepthStencilBuffer = nullptr;

	return 1;	//Return True
}

int Engine::DX11Renderer::InitializeDefaultShader(LPCWSTR a_ShaderPath, int a_MaxVertices)
{
	//---------------------------------------------------------------
	//	Create Initialize Types
	//---------------------------------------------------------------

	ID3D11VertexShader* pVS = nullptr;
	ID3D11PixelShader* pPS = nullptr;
	ID3DBlob* pVSBlob = nullptr;
	ID3DBlob* pPSBlob = nullptr;
	ID3D11InputLayout* pLayout = nullptr;
	D3D11_BUFFER_DESC vertexBufferDesc = { 0 };
	UINT stride = sizeof(Shader::S_Vertex);
	UINT offset = 0;

	//---------------------------------------------------------------
	//	Load, Create and Set Shader
	//---------------------------------------------------------------

	D3DCompileFromFile(a_ShaderPath, 0, 0, "VS_Main", "vs_5_0", 0, 0, &pVSBlob, 0);
	D3DCompileFromFile(a_ShaderPath, 0, 0, "PS_Main", "ps_5_0", 0, 0, &pPSBlob, 0);

	if (m_pDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &pVS) != S_OK)
	{
		return -8;
	}
	if (m_pDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &pPS) != S_OK)
	{
		return -9;
	}

	m_pContext->VSSetShader(pVS, NULL, 0);
	m_pContext->PSSetShader(pPS, NULL, 0);

	//---------------------------------------------------------------
	//	Create and Set Shader InputLayout
	//---------------------------------------------------------------

	D3D11_INPUT_ELEMENT_DESC InputElementDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	if (m_pDevice->CreateInputLayout(InputElementDesc, ARRAYSIZE(InputElementDesc), pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &pLayout) != S_OK)
	{
		return -10;
	}
	m_pContext->IASetInputLayout(pLayout);

	//---------------------------------------------------------------
	//	Fill VertexBuffer Description and Create Buffer
	//---------------------------------------------------------------

	ZeroMemory(&vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(Shader::S_Vertex) * a_MaxVertices;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	m_pDevice->CreateBuffer(&vertexBufferDesc, NULL, &m_pVertexBuffer);
	m_pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	//---------------------------------------------------------------
	//	Release
	//---------------------------------------------------------------

	if (pVS != nullptr)
	{

		pVS->Release();
		pVS = nullptr;
	}

	if (pVS != nullptr)
	{
		pPS->Release();
		pPS = nullptr;
	}

	if (pVS != nullptr)
	{
		pVSBlob->Release();
		pVSBlob = nullptr;
	}

	if (pVS != nullptr)
	{
		pPSBlob->Release();
		pPSBlob = nullptr;
	}

	if (pVS != nullptr)
	{
		pLayout->Release();
		pLayout = nullptr;
	}

	return 1;	//Return True
}

int Engine::DX11Renderer::InitializeVSConstantBuffer()
{
	//---------------------------------------------------------------
	//	Create Initialize Types
	//---------------------------------------------------------------

	D3D11_BUFFER_DESC constantBufferDesc = { 0 };

	//---------------------------------------------------------------
	//	Fill VShader ConstantBuffer Description and Create Buffer
	//---------------------------------------------------------------

	constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	constantBufferDesc.ByteWidth = sizeof(Shader::S_VSConstantBufferData);
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBufferDesc.MiscFlags = 0;
	constantBufferDesc.StructureByteStride = 0;

	if(m_pDevice->CreateBuffer(&constantBufferDesc, 0, &m_pVSConstantBuffer) != S_OK)
	{
		return -11;
	}
	m_pContext->VSSetConstantBuffers(0, 1, &m_pVSConstantBuffer);

	m_pContext->Map(m_pVSConstantBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &m_MappedSubResource);
	m_pVSConstantBufferData = (Shader::S_VSConstantBufferData*)m_MappedSubResource.pData;
	m_pContext->Unmap(m_pVSConstantBuffer, NULL);

	return 1;	//Return True
}

int Engine::DX11Renderer::InitializePSConstantBuffer()
{
	//---------------------------------------------------------------
	//	Create Initialize Types
	//---------------------------------------------------------------

	D3D11_BUFFER_DESC constantBufferDesc = { 0 };

	//---------------------------------------------------------------
	//	Fill PShader ConstantBuffer Description and Create Buffer
	//---------------------------------------------------------------

	constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	constantBufferDesc.ByteWidth = sizeof(Shader::S_PSConstantBufferData);
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBufferDesc.MiscFlags = 0;
	constantBufferDesc.StructureByteStride = 0;

	if(m_pDevice->CreateBuffer(&constantBufferDesc, 0, &m_pPSConstantBuffer) != S_OK)
	{
		return -12;
	}
	m_pContext->PSSetConstantBuffers(0, 1, &m_pPSConstantBuffer);

	m_pContext->Map(m_pPSConstantBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &m_MappedSubResource);
	m_pPSConstantBufferData = (Shader::S_PSConstantBufferData*)m_MappedSubResource.pData;
	m_pContext->Unmap(m_pPSConstantBuffer, NULL);

	return 1;	//Return True
}
