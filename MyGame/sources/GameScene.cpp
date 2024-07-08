#include "GameScene.h"
#include "StelEngine.h"
#include "PlayerControls.h"
#include "StelSprite.h"


void GameScene::Load()
{
	m_Player = Stel::Engine::Get().GetWorld().Create("Player");

	StelSprite* model = m_Player->AddComponent<StelSprite>();
	model->Init("Assets/adv_lolo_char.png", { 0, 0, 15, 15 }, { 200.0f, 200.0f, 64.0f, 64.0f })->Start();

	PlayerControls* playerControls = m_Player->AddComponent<PlayerControls>();
	playerControls->SetPostion({ 400.0f, 400.0f });
	playerControls->SetSpeed(15.0f);
	playerControls->Start();


	
}