#include "DX11Window.h"

Engine::DX11Window::DX11Window()
{
}

Engine::DX11Window::~DX11Window()
{
}

//Handle Events
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);			
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}


void Engine::DX11Window::Initialize(Engine::S_DX11WindowDesc* a_DX11WindowDesc)
{
	m_DX11WindowDesc = *a_DX11WindowDesc;

	//---------------------------------------------------------------
	//	Initialize WNDCLASS
	//---------------------------------------------------------------

	WNDCLASS WNDClass;

	ZeroMemory(&WNDClass, sizeof(WNDCLASS));
	WNDClass.cbClsExtra = 0;
	WNDClass.cbWndExtra = 0;
	WNDClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WNDClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WNDClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WNDClass.hInstance = m_DX11WindowDesc.Instance;
	WNDClass.lpfnWndProc = WndProc;
	WNDClass.lpszClassName = L"CubeRotator5000 | FPS: 60 ";
	WNDClass.lpszMenuName = NULL;
	WNDClass.style = CS_HREDRAW | CS_VREDRAW;
	
	RegisterClass(&WNDClass);

	//---------------------------------------------------------------
	//	Create, Show and Update HWND
	//---------------------------------------------------------------

	m_DX11WindowDesc.Hwnd = CreateWindow(WNDClass.lpszClassName, WNDClass.lpszClassName, WS_OVERLAPPEDWINDOW, 0, 0, m_DX11WindowDesc.Resolution[0], m_DX11WindowDesc.Resolution[1], NULL, NULL, m_DX11WindowDesc.Instance, NULL);

	ShowWindow(m_DX11WindowDesc.Hwnd, m_DX11WindowDesc.CmdShow);
	UpdateWindow(m_DX11WindowDesc.Hwnd);
}

Engine::S_DX11WindowDesc* Engine::DX11Window::GetWindowDesc()
{
	return &m_DX11WindowDesc;
}

