#pragma once
#include <D3D11.h>
#pragma comment(lib, "D3D11.lib")
#include <d3dcompiler.h>
#pragma comment(lib, "D3DCompiler.lib")
#include <vector>
#include <DirectXMath.h>
#include "..\..\Types.h"

namespace Engine
{
	class DX11Renderer
	{

	#pragma region Variables
	public:

	private:

		ID3D11Device* m_pDevice										= nullptr;
		IDXGISwapChain* m_pSwapChain								= nullptr;
		ID3D11DeviceContext* m_pContext								= nullptr;
		ID3D11RenderTargetView* m_pBackBufferView					= nullptr;
		ID3D11DepthStencilView* m_pDepthStencilView					= nullptr;
		ID3D11Buffer *m_pVertexBuffer								= nullptr;
		ID3D11Buffer* m_pVSConstantBuffer							= nullptr;
		ID3D11Buffer* m_pPSConstantBuffer							= nullptr;

		D3D11_MAPPED_SUBRESOURCE m_MappedSubResource				= { 0 };

		Shader::S_VSConstantBufferData* m_pVSConstantBufferData		= nullptr;
		Shader::S_PSConstantBufferData* m_pPSConstantBufferData		= nullptr;

		S_DX11RendererDesc m_DX11RendererDesc;


#pragma endregion

#pragma region Methods
	public:
		DX11Renderer();
		~DX11Renderer();
		int Initialize(Engine::S_DX11WindowDesc* a_DX11WindowDesc, Engine::S_DX11RendererDesc* a_DX11RendererDesc);
		
		//Render Methods
		void Begin(float a_clearColor[4]);
		void Render(std::vector<Shader::S_Vertex> a_Vertices, Engine::E_RenderType a_RenderType = Engine::E_RenderType::TriangleStrip);
		void End();
		
		//Shader Methods
		int LoadShader(Engine::E_ShaderType a_ShaderType, D3D11_INPUT_ELEMENT_DESC* a_InputElementDesc, UINT a_InputElementArraySize, LPCWSTR a_ShaderPath, char* a_ShaderEntryPoint, char* a_ShaderModel);
		void FillVSShaderData(Shader::S_VSConstantBufferData* a_ShaderData);
		void FillPSShaderData(Shader::S_PSConstantBufferData* a_ShaderData);
				
		Engine::S_DX11RendererDesc* GetRendererDesc();
	private:

		int InitializeDirectX11(Engine::S_DX11WindowDesc* a_DX11WindowDesc, Engine::S_DX11RendererDesc* a_DX11RendererDesc);
		int InitializeDefaultShader(LPCWSTR a_ShaderPath, int a_MaxVertices);

		int InitializeVSConstantBuffer();
		int InitializePSConstantBuffer();

#pragma endregion
	};
}
