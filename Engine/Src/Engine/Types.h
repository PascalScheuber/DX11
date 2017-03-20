#pragma once
#include <Windows.h>
#include "Shader.h"


namespace Engine
{
	//---------------------------------------------------------------
	//	DX11 Window
	//---------------------------------------------------------------

	struct S_DX11WindowDesc
	{
		int Resolution[2] = { 1280, 720 };
		HINSTANCE Instance = NULL;
		HWND Hwnd = NULL;
		int CmdShow = 1;
		bool Fullscreen = false;
	};

	//---------------------------------------------------------------
	//	DX11 Renderer
	//---------------------------------------------------------------

	enum class E_RenderType : short
	{
		None,
		TriangleList,
		TriangleStrip,
	};

	struct S_DX11RendererDesc
	{
		E_RenderType RenderType = E_RenderType::TriangleStrip;

		LPCWSTR ShaderPath = L"Data\\Shader\\DefaultShader.shader";
		int MaxVerticesPerRender = 100;
		int FixedFPS = 0;
	};

	//---------------------------------------------------------------
	//	Camera
	//---------------------------------------------------------------

	struct S_CameraDesc
	{
		int Resolution[2] = { 1280, 720 };
		float NearPlane = 0.1f;
		float FarPlane = 1000.0f;
		float FoV = 80;
	};

	//---------------------------------------------------------------
	//	Shader
	//---------------------------------------------------------------

	enum class E_ShaderType : short
	{
		None,
		VertexShader,
		PixelShader,
	};
}