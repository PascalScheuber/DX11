#include "Camera.h"

Engine::Camera::Camera()
{
}

Engine::Camera::~Camera()
{
}

void Engine::Camera::Initialize(Engine::S_CameraDesc* a_CameraDesc)
{
	m_CameraDesc = *a_CameraDesc;

	CalculateLookDirection();
	CalculateUp();

	CalculateViewMatrix();
	CalculateProjectionMatrix();
}

void Engine::Camera::Initialize(Engine::S_CameraDesc* a_CameraDesc, DirectX::XMVECTOR a_Position, DirectX::XMVECTOR a_Target)
{
	m_CameraDesc = *a_CameraDesc;
	m_Position = a_Position;
	m_Target = a_Target;

	CalculateLookDirection();
	CalculateUp();

	CalculateViewMatrix();
	CalculateProjectionMatrix();
}

void Engine::Camera::SetPosition(DirectX::XMVECTOR a_Position)
{
	m_Position = a_Position;

	CalculateLookDirection();
	CalculateUp();
	CalculateViewMatrix();
}

void Engine::Camera::SetTarget(DirectX::XMVECTOR a_Target)
{
	m_Target = a_Target;

	CalculateLookDirection();
	CalculateUp();
	CalculateViewMatrix();
}

DirectX::XMVECTOR Engine::Camera::GetPosition()
{
	return m_Position;
}

DirectX::XMVECTOR Engine::Camera::GetLookDirection()
{
	return m_LookDirection;
}

DirectX::XMMATRIX Engine::Camera::GetViewMatrix()
{
	return m_ViewMatrix;
}

DirectX::XMMATRIX Engine::Camera::GetProjectionMatrix()
{
	return m_ProjectionMatrix;
}

Engine::S_CameraDesc * Engine::Camera::GetCameraDesc()
{
	return &m_CameraDesc;
}

void Engine::Camera::CalculateLookDirection()
{
	m_LookDirection = DirectX::XMVectorSubtract(m_Target, m_Position);
	m_LookDirection = DirectX::XMVector3Normalize(m_LookDirection);
}

void Engine::Camera::CalculateUp()
{
	m_Up = DirectX::XMVector3Cross(DirectX::XMVector3Cross(m_LookDirection, DirectX::XMVECTOR{ 0, 1, 0 }), m_LookDirection);
}

void Engine::Camera::CalculateViewMatrix()
{
	m_ViewMatrix = DirectX::XMMatrixLookAtLH(m_Position, m_Target, m_Up);
}

void Engine::Camera::CalculateProjectionMatrix()
{
	m_ProjectionMatrix = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(m_CameraDesc.FoV), (float)m_CameraDesc.Resolution[0] / (float)m_CameraDesc.Resolution[1],
						m_CameraDesc.NearPlane, m_CameraDesc.FarPlane);
}
