#include "AmbientLight.h"

Engine::AmbientLight::AmbientLight()
{
}

Engine::AmbientLight::~AmbientLight()
{
}

void Engine::AmbientLight::SetLightColor(DirectX::XMFLOAT4 a_LightColor)
{
	m_LightColor = a_LightColor;
}

void Engine::AmbientLight::SetLightIntensity(float a_LightIntensity)
{
	m_LightIntensity = a_LightIntensity;
}

DirectX::XMFLOAT4 Engine::AmbientLight::GetLightColor()
{
	return m_LightColor;
}

float Engine::AmbientLight::GetLightIntensity()
{
	return m_LightIntensity;
}
