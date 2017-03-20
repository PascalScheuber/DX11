#pragma once
#include <DirectXMath.h>

namespace Engine
{
	class PointLight
	{
	#pragma region Variables
	public:

	private:
		DirectX::XMVECTOR m_Position = { 0,1,-2 };
		DirectX::XMFLOAT4 m_LightColor = { 1,1,1,1 };
		float m_LightIntensity = 1.0f;
		float m_LightRadius = 1.0f;

	#pragma endregion

	#pragma region Methods
	public:
		PointLight();
		~PointLight();

		void SetPosition(DirectX::XMVECTOR a_Position);
		void SetLightColor(DirectX::XMFLOAT4 a_LightColor);
		void SetLightRadius(float a_LightRadius);
		void SetLightIntensity(float a_LightIntensity);

		DirectX::XMVECTOR GetPosition();
		DirectX::XMFLOAT4 GetLightColor();
		float GetLightRadius();
		float GetLightIntensity();

	private:

	#pragma endregion
	};
}
