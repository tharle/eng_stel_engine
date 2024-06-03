#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#include "Engine.h"

#ifdef  _DEBUG
#include "vld.h"
#endif //  _DEBUG



void InitGameplay()
{

}

INT WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ PSTR, _In_ INT)
{
	StelEngine::Engine stelEngine;
	if (stelEngine.Init("Legends of Stel", 800, 600))
	{
		InitGameplay();
		stelEngine.Start();
	}
	return 0;
}