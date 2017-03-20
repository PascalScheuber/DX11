#include "Cube.h"

Engine::PrimitiveType::Cube::Cube()
{
	InitializeVertices();
	SetDebugVertices();
}

Engine::PrimitiveType::Cube::Cube(DirectX::XMFLOAT3 a_Position, DirectX::XMFLOAT3 a_Scale, DirectX::XMFLOAT4 a_Color)
{
	m_Position = a_Position;
	m_Scale = a_Scale;
	m_Color = a_Color;

	InitializeVertices();
	SetDebugVertices();
}

Engine::PrimitiveType::Cube::~Cube()
{
}

void Engine::PrimitiveType::Cube::Rotate(DirectX::XMVECTOR a_Axis, DirectX::XMVECTOR a_Angle)
{
	m_WorldMatrix *= DirectX::XMMatrixRotationRollPitchYaw(a_Axis.m128_f32[0] * DirectX::XMConvertToRadians(a_Angle.m128_f32[0]), a_Axis.m128_f32[1] * DirectX::XMConvertToRadians(a_Angle.m128_f32[1]), a_Axis.m128_f32[2] * DirectX::XMConvertToRadians(a_Angle.m128_f32[2]));
}

void Engine::PrimitiveType::Cube::SetPosition(DirectX::XMFLOAT3 a_Position)
{
	m_Position = a_Position;
}

void Engine::PrimitiveType::Cube::SetScale(DirectX::XMFLOAT3 a_Scale)
{
	ScaleVertices(a_Scale);
	m_Scale = a_Scale;
	SetDebugVertices();
}

void Engine::PrimitiveType::Cube::SetColor(DirectX::XMFLOAT4 a_Color)
{
	m_Color = a_Color;
}

DirectX::XMMATRIX Engine::PrimitiveType::Cube::GetWorldMatrix()
{
	return m_WorldMatrix;
}

std::vector<Shader::S_Vertex> Engine::PrimitiveType::Cube::GetVertices()
{
	return m_Vertices;
}

std::vector<std::vector<Shader::S_Vertex>> Engine::PrimitiveType::Cube::GetDebugVertices()
{
	return m_DebugVertices;
}

void Engine::PrimitiveType::Cube::InitializeVertices()
{
	m_Vertices.resize(24);

	// Front
	m_Vertices[0] = {  -0.5f, -0.5f, -0.5f	, 0.0f, 0.0f, -1.0f };		// Front BL
	m_Vertices[1] = {  -0.5f,  0.5f, -0.5f	, 0.0f, 0.0f, -1.0f };		// Front TL
	m_Vertices[2] = {	0.5f, -0.5f, -0.5f	, 0.0f, 0.0f, -1.0f };		// Front BR
	m_Vertices[3] = {	0.5f,  0.5f, -0.5f	, 0.0f, 0.0f, -1.0f };		// Front TR

	// Left
	m_Vertices[4] = {  -0.5f, -0.5f,  0.5f	, -1.0f, 0.0f, 0.0f };		// Back BL
	m_Vertices[5] = {  -0.5f,  0.5f,  0.5f	, -1.0f, 0.0f, 0.0f };		// Back TL
	m_Vertices[6] = {  -0.5f, -0.5f, -0.5f	, -1.0f, 0.0f, 0.0f };		// Front BL
	m_Vertices[7] = {  -0.5f,  0.5f, -0.5f	, -1.0f, 0.0f, 0.0f };		// Front TL

	// Back
	m_Vertices[8] =  {	0.5f, -0.5f,  0.5f	, 0.0f, 0.0f, 1.0f };		// Back BR
	m_Vertices[9] =	 {	0.5f,  0.5f,  0.5f	, 0.0f, 0.0f, 1.0f };		// Back TR
	m_Vertices[10] = { -0.5f, -0.5f,  0.5f	, 0.0f, 0.0f, 1.0f };		// Back BL
	m_Vertices[11] = { -0.5f,  0.5f,  0.5f	, 0.0f, 0.0f, 1.0f };		// Back TL

	// Right
	m_Vertices[12] = {	0.5f, -0.5f, -0.5f	, 1.0f, 0.0f, 0.0f };		// Front BR
	m_Vertices[13] = {	0.5f,  0.5f, -0.5f	, 1.0f, 0.0f, 0.0f };		// Front TR
	m_Vertices[14] = {	0.5f, -0.5f,  0.5f	, 1.0f, 0.0f, 0.0f };		// Back BR
	m_Vertices[15] = {	0.5f,  0.5f,  0.5f	, 1.0f, 0.0f, 0.0f };		// Back TR

	// Bottom  
	m_Vertices[16] = { -0.5f, -0.5f,  0.5f	, 0.0f, -1.0f, 0.0f };		// Back BL
	m_Vertices[17] = { -0.5f, -0.5f, -0.5f	, 0.0f, -1.0f, 0.0f };		// Front BL
	m_Vertices[18] = {	0.5f, -0.5f,  0.5f	, 0.0f, -1.0f, 0.0f };		// Back BR
	m_Vertices[19] = {	0.5f, -0.5f, -0.5f	, 0.0f, -1.0f, 0.0f };		// Front BR

	// Top
	m_Vertices[20] = { -0.5f,  0.5f, -0.5f	, 0.0f, 1.0f, 0.0f };		// Front TL
	m_Vertices[21] = { -0.5f,  0.5f,  0.5f	, 0.0f, 1.0f, 0.0f };		// Back TL
	m_Vertices[22] = {	0.5f,  0.5f, -0.5f	, 0.0f, 1.0f, 0.0f };		// Front TR
	m_Vertices[23] = {	0.5f,  0.5f,  0.5f	, 0.0f, 1.0f, 0.0f };		// Back TR
	
	for (int i = 0; i < 24; i++)
	{
		m_Vertices[i].Color[0] = m_Color.x;
		m_Vertices[i].Color[1] = m_Color.y;
		m_Vertices[i].Color[2] = m_Color.z;
		m_Vertices[i].Color[3] = m_Color.w;

		m_Vertices[i].Position[0] *= m_Scale.x;
		m_Vertices[i].Position[1] *= m_Scale.y;
		m_Vertices[i].Position[2] *= m_Scale.z;
	}
}

void Engine::PrimitiveType::Cube::SetDebugVertices()
{
	//TODO: Optimize

	m_DebugVertices.clear();

	std::vector<Shader::S_Vertex> vertexList;

	DirectX::XMFLOAT4 Color;

	for (int i = 0; i < 6; i++)
	{
		vertexList.clear();

		switch (i)
		{
		case 0:
			Color = { 1,0,0,1 };
			break;
		case 1:
			Color = { 0,1,0,1 };
			break;
		case 2:
			Color = { 0,0,1,1 };
			break;
		case 3:
			Color = { 1,1,0,1 };
			break;
		case 4:
			Color = { 1,0,1,1 };
			break;
		case 5:
			Color = { 0,1,1,1 };
			break;
		}
		vertexList.push_back(Shader::S_Vertex{ m_Vertices[0 + (i * 4)].Position[0], m_Vertices[0 + (i * 4)].Position[1], m_Vertices[0 + (i * 4)].Position[2], m_Vertices[0 + (i * 4)].Normal[0], m_Vertices[0 + (i * 4)].Normal[1], m_Vertices[0 + (i * 4)].Normal[2], Color.x, Color.y, Color.z, Color.w });
		vertexList.push_back(Shader::S_Vertex{ m_Vertices[1 + (i * 4)].Position[0], m_Vertices[1 + (i * 4)].Position[1], m_Vertices[1 + (i * 4)].Position[2], m_Vertices[1 + (i * 4)].Normal[0], m_Vertices[1 + (i * 4)].Normal[1], m_Vertices[1 + (i * 4)].Normal[2], Color.x, Color.y, Color.z, Color.w });
		vertexList.push_back(Shader::S_Vertex{ m_Vertices[2 + (i * 4)].Position[0], m_Vertices[2 + (i * 4)].Position[1], m_Vertices[2 + (i * 4)].Position[2], m_Vertices[2 + (i * 4)].Normal[0], m_Vertices[2 + (i * 4)].Normal[1], m_Vertices[2 + (i * 4)].Normal[2], Color.x, Color.y, Color.z, Color.w });
		vertexList.push_back(Shader::S_Vertex{ m_Vertices[3 + (i * 4)].Position[0], m_Vertices[3 + (i * 4)].Position[1], m_Vertices[3 + (i * 4)].Position[2], m_Vertices[3 + (i * 4)].Normal[0], m_Vertices[3 + (i * 4)].Normal[1], m_Vertices[3 + (i * 4)].Normal[2], Color.x, Color.y, Color.z, Color.w });
		
		m_DebugVertices.push_back(vertexList);		
	}
}

void Engine::PrimitiveType::Cube::ScaleVertices(DirectX::XMFLOAT3 a_NewScale)
{
	for (int i = 0; i < 24; i++)
	{
		m_Vertices[i].Position[0] = (m_Vertices[i].Position[0] / m_Scale.x) * a_NewScale.x;
		m_Vertices[i].Position[1] = (m_Vertices[i].Position[1] / m_Scale.y) * a_NewScale.y;
		m_Vertices[i].Position[2] = (m_Vertices[i].Position[2] / m_Scale.z) * a_NewScale.z;
	}
}

