#include "GameScene.h"
#include "StelEngine.h"
#include "PlayerControls.h"


GameScene::~GameScene() 
{
	if (m_Player != nullptr) 
	{
		m_Player->Destroy();
		delete m_Player;
		m_Player = nullptr;
	}
}

void GameScene::Load()
{
	m_Player = Stel::Engine::Get().GetWorld().Create("Player");
	PlayerControls* playerControls = m_Player->AddComponent<PlayerControls>();
	
	playerControls->Start();
	playerControls->SetPostion({ 400.0f, 400.0f });
	playerControls->SetSpeed(15.0f);
	playerControls->Start();
	
}