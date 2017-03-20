#pragma once
#include <DirectXMath.h>

namespace Engine
{
	class AmbientLight
	{
	#pragma region Variables
	public:

	private:
		DirectX::XMFLOAT4 m_LightColor = { 1,1,1,1 };
		float m_LightIntensity = 0.5f;
		
	#pragma endregion

	#pragma region Methods
	public:
		AmbientLight();
		~AmbientLight();

		void SetLightColor(DirectX::XMFLOAT4 a_LightColor);
		void SetLightIntensity(float a_LightIntensity);

		DirectX::XMFLOAT4 GetLightColor();
		float GetLightIntensity();
		
	private:

	#pragma endregion
	};
}
