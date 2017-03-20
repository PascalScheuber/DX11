#pragma once
#include <DirectXMath.h>

namespace Shader
{

	//---------------------------------------------------------------
	//	Vertex- Pixel-Shader ConstantBuffer Type
	//
	//  NOTE: Editable to Change Shader ConstantBuffer Input
	//  NOTE: Care 16Byte alignment!
	//---------------------------------------------------------------

	struct S_VSConstantBufferData
	{
		DirectX::XMMATRIX World;
		DirectX::XMMATRIX View;
		DirectX::XMMATRIX Projection;
	};

	struct S_PSConstantBufferData
	{
		float ViewDirection[3] = { 0.0f, 0.0f, 0.0f };
		float AmbientIntensity = 1.0f;
		float AmbientLightColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		float LightColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		float LightPosition[3] = { 0.0f, 0.0f, 0.0f };
		float LightIntensity = 1.0f;
		float LightRadius = 1.0f;
		float ByteFiller[3] = { 0 };
	};

	//---------------------------------------------------------------
	//	VertexBuffer Type
	//
	//  NOTE: Editable to Change Shader Layout Input
	//---------------------------------------------------------------

	struct S_Vertex
	{
		float Position[3];
		float Normal[3];
		float Color[4];
	};

}