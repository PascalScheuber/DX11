#pragma once
#include <Windows.h>
#include "..\..\Types.h"

namespace Engine
{
	class DX11Window
	{
	#pragma region Variables
	public:

	private:

		S_DX11WindowDesc m_DX11WindowDesc;

	#pragma endregion

	#pragma region Methods
	public:
		DX11Window();
		~DX11Window();

		void Initialize(Engine::S_DX11WindowDesc* a_DX11WindowDesc);

		Engine::S_DX11WindowDesc* GetWindowDesc();

	private:

	#pragma endregion
	};
}
