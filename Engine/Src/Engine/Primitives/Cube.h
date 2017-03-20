#pragma once
#include <DirectXMath.h>
#include "iPrimitive.h"
#include "..\Types.h"

namespace Engine
{
	namespace PrimitiveType
	{
		class Cube : public iPrimitiv
		{
		#pragma region Variables
		public:

		private:
			DirectX::XMFLOAT3 m_Position = { 0.0f, 0.0f, 0.0f };
			DirectX::XMFLOAT3 m_Scale = { 1.0f, 1.0f, 1.0f };
			DirectX::XMFLOAT4 m_Color = { 0.0f, 1.0f, 1.0f, 1.0f };

			DirectX::XMMATRIX m_WorldMatrix = DirectX::XMMatrixIdentity();

			std::vector<Shader::S_Vertex> m_Vertices;	//RenderType TriangleStrip

		#pragma endregion

		#pragma region Methods
		public:
			Cube();
			Cube(DirectX::XMFLOAT3 a_Position, DirectX::XMFLOAT3 a_Scale, DirectX::XMFLOAT4 a_Color);
			~Cube();;

			void Rotate(DirectX::XMVECTOR a_Axis, DirectX::XMVECTOR a_Angle);

			void SetPosition(DirectX::XMFLOAT3 a_Position);
			void SetScale(DirectX::XMFLOAT3 a_Scale);
			void SetColor(DirectX::XMFLOAT4 a_Color);

			DirectX::XMMATRIX GetWorldMatrix();
			std::vector<Shader::S_Vertex> GetVertices();
			std::vector<std::vector<Shader::S_Vertex>> GetDebugVertices() override;
						
		private:

			void InitializeVertices();

			void SetDebugVertices();

			void ScaleVertices(DirectX::XMFLOAT3 a_NewScale);

		#pragma endregion
		};
	}
}
