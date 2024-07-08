#include "GameScene.h"
#include "StelEngine.h"
#include "PlayerControls.h"


void GameScene::Load()
{
	m_Player = Stel::Engine::Get().GetWorld().Create("Player");
	PlayerControls* playerControls = m_Player->AddComponent<PlayerControls>();
	
	playerControls->Start();
	playerControls->SetPostion({ 400.0f, 400.0f });
	playerControls->SetSpeed(15.0f);
	playerControls->Start();
	
}