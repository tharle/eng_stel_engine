#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#include "StelEngine.h"
#include "MainMenuScene.h"
#include "GameScene.h"

#ifdef  _DEBUG
#include "vld.h"
#endif //  _DEBUG


MainMenuScene* mainMenuScene;
GameScene* gameScene;

void InitGameplay()
{
	mainMenuScene = new MainMenuScene();
	gameScene = new GameScene();

	Stel::Engine::Get().GetWorld().Register("MainMenu", mainMenuScene);
	Stel::Engine::Get().GetWorld().Register("Game", gameScene);
	Stel::Engine::Get().GetWorld().LoadScene("MainMenu");

}

INT WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ PSTR, _In_ INT)
{
	if (Stel::Engine::Get().Init("Legends of Stel", { 800, 600 }))
	{
		InitGameplay();
		Stel::Engine::Get().Start();
	}
	return 0;
}