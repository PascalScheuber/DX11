#include "PointLight.h"

Engine::PointLight::PointLight()
{
}

Engine::PointLight::~PointLight()
{
}

void Engine::PointLight::SetPosition(DirectX::XMVECTOR a_Position)
{
	m_Position = a_Position;
}

void Engine::PointLight::SetLightColor(DirectX::XMFLOAT4 a_LightColor)
{
	m_LightColor = a_LightColor;
}

void Engine::PointLight::SetLightRadius(float a_LightRadius)
{
	m_LightRadius = a_LightRadius;
}

void Engine::PointLight::SetLightIntensity(float a_LightIntensity)
{
	m_LightIntensity = a_LightIntensity;
}

DirectX::XMVECTOR Engine::PointLight::GetPosition()
{
	return m_Position;
}

DirectX::XMFLOAT4 Engine::PointLight::GetLightColor()
{
	return m_LightColor;
}

float Engine::PointLight::GetLightRadius()
{
	return m_LightRadius;
}


float Engine::PointLight::GetLightIntensity()
{
	return m_LightIntensity;
}
