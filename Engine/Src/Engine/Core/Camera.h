#pragma once
#include <DirectXMath.h>
#include "..\Types.h"

namespace Engine
{
	class Camera
	{
	#pragma region Variables
	public:

	private:

		Engine::S_CameraDesc m_CameraDesc;

		DirectX::XMVECTOR m_Position = { 0.0f, 0.0f, -1.0f };
		DirectX::XMVECTOR m_Target = { 0.0f, 0.0f, 0.0f };
		DirectX::XMVECTOR m_LookDirection = { 0.0f, 0.0f, 1.0f };
		DirectX::XMVECTOR m_Up = { 0.0f, 1.0f, 0.0f };

		DirectX::XMMATRIX m_ViewMatrix;
		DirectX::XMMATRIX m_ProjectionMatrix;
				
	#pragma endregion

	#pragma region Methods
	public:
		Camera();
		~Camera();

		void Initialize(Engine::S_CameraDesc* a_CameraDesc);
		void Initialize(Engine::S_CameraDesc* a_CameraDesc, DirectX::XMVECTOR a_Position, DirectX::XMVECTOR a_Target);

		void SetPosition(DirectX::XMVECTOR a_Position);
		void SetTarget(DirectX::XMVECTOR a_Target);

		DirectX::XMVECTOR GetPosition();
		DirectX::XMVECTOR GetLookDirection();
		DirectX::XMMATRIX GetViewMatrix();
		DirectX::XMMATRIX GetProjectionMatrix();
		Engine::S_CameraDesc* GetCameraDesc();

	private:

		void CalculateLookDirection();
		void CalculateUp();

		void CalculateViewMatrix();
		void CalculateProjectionMatrix();
		
	#pragma endregion
	};
}
