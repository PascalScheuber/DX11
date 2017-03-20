// -----------------------------------------------------------
//		Developed & Tested only on Windows 10 64Bit
// -----------------------------------------------------------

#include "CubeRotator5000.h"

#if _DEBUG
int main(HINSTANCE a_instance, HINSTANCE a_prevInstance, LPSTR a_cmd, int a_cmdShow)
#else
int WINAPI WinMain(HINSTANCE a_instance, HINSTANCE a_prevInstance, LPSTR a_cmd, int a_cmdShow)
#endif
{
	CubeRotator5000 cubeRotator5000;

	while (!cubeRotator5000.GetQuit())
	{
		cubeRotator5000.Update();
	}

	return 0;
}