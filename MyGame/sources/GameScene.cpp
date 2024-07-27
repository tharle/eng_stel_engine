#include "GameScene.h"
#include "StelEngine.h"
#include "PlayerControls.h"
#include "StelAnimation.h"
#include "LevelManager.h"


void GameScene::Load()
{
	float scaleFactor = 2;
	m_Level  = Instantiate("Level");

	LevelManager* levelManager = m_Level->AddComponent<LevelManager>();
	levelManager->Start();


	m_Player = Instantiate("Player");
	m_Player->SetTransform({ 200.0f, 300.0f }, { 16, 16 }, scaleFactor, 0.0f);

	StelAnimation* model = m_Player->AddComponent<StelAnimation>();
	model->Init("Assets/adv_lolo_char.png");
	model->Start();
	model->AddAnimationFrames(5, { 0, 0 }, {16, 16});
	model->AddAnimationFrames(5, { 0, 16 }, {16, 16});
	model->AddAnimationFrames(5, { 0, 32 }, {16, 16});
	model->AddAnimationFrames(5, { 0, 48 }, {16, 16});

	PlayerControls* playerControls = m_Player->AddComponent<PlayerControls>();


	playerControls->Start(levelManager, 5.0f);
	
}