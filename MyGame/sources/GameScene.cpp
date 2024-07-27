#include "GameScene.h"
#include "StelEngine.h"
#include "PlayerControls.h"
#include "StelAnimation.h"
#include "LevelManager.h"
#include "Collectable.h";


void GameScene::Load()
{
	float scaleFactor = 2;
	m_Level  = Instantiate("Level");
	m_Level->SetTransform(StelPointF::Zero(), {16.0f, 16.0f}, scaleFactor, 0.0f);

	LevelManager* levelManager = m_Level->AddComponent<LevelManager>();
	levelManager->Start();

	m_Player = Instantiate("Player");
	m_Player->SetTransform({ 200.0f, 300.0f }, { 16.0f, 16.0f }, scaleFactor, 0.0f);
	PlayerControls* playerControls = m_Player->AddComponent<PlayerControls>();
	playerControls->Start(levelManager, 5.0f);

	m_Heart = Instantiate("Item1");
	m_Heart->SetTransform({ 2.0f * 16, 2.0f * 16 }, { 16.0f, 16.0f }, scaleFactor, 0.0f);
	Collectable* heart1 = m_Heart->AddComponent<Collectable>();
	heart1->Start();
	
}