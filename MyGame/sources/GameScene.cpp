#include "GameScene.h"
#include "StelEngine.h"
#include "PlayerControls.h"
#include "StelAnimation.h"
#include "LevelManager.h"


void GameScene::Load()
{
	m_Player = Instantiate("Player");

	LevelManager* gameManager = m_Player->AddComponent<LevelManager>();
	gameManager->Start();

	StelAnimation* model = m_Player->AddComponent<StelAnimation>();
	model->Init("Assets/adv_lolo_char.png", { 16, 16 }, 2);
	model->Start();
	model->AddAnimationFrames(5, { 0, 0 }, {16, 16});
	model->AddAnimationFrames(5, { 0, 16 }, {16, 16});
	model->AddAnimationFrames(5, { 0, 32 }, {16, 16});
	model->AddAnimationFrames(5, { 0, 48 }, {16, 16});

	PlayerControls* playerControls = m_Player->AddComponent<PlayerControls>();
	playerControls->SetPostion({ 200.0f, 300.0f });
	playerControls->SetSpeed(15.0f);
	playerControls->Start();
	
}