#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#include "StelEngine.h"
#include "PlayerControls.h"

#ifdef  _DEBUG
#include "vld.h"
#endif //  _DEBUG


StelEntity* player;
PlayerControls* playerControls;

void InitGameplay()
{
	player = Stel::Engine::Get().GetWorld().Create("Player");
	playerControls = player->AddComponent<PlayerControls>();
	playerControls->Start();
	playerControls->SetPostion({ 400.0f, 400.0f });
	playerControls->SetSpeed(15.0f);
}

INT WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ PSTR, _In_ INT)
{
	if (Stel::Engine::Get().Init("Legends of Stel", 800, 600))
	{
		InitGameplay();
		Stel::Engine::Get().Start();
	}
	return 0;
}