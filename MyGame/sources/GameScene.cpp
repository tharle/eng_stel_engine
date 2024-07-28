#include "GameScene.h"
#include "StelEngine.h"
#include "PlayerControls.h"
#include "StelAnimation.h"
#include "LevelManager.h"
#include "Collectable.h";
#include "Chest.h";


void GameScene::Load()
{
	float scaleFactor = 2;
	m_Level  = Instantiate("Level");
	m_Level->SetTransform(StelPointF::Zero(), {16.0f, 16.0f}, scaleFactor, 0.0f);

	LevelManager* levelManager = m_Level->AddComponent<LevelManager>();
	levelManager->Start();

	m_Heart1 = Instantiate("Item1");
	m_Heart1->SetTransform({ 6.0f * 32.0f, 3.0f * 32.0f }, { 16.0f, 16.0f }, scaleFactor, 0.0f);
	Collectable* c1 = m_Heart1->AddComponent<Collectable>();
	c1->Start();

	m_Heart2 = Instantiate("Item2");
	m_Heart2->SetTransform({ 12.0f * 32.0f, 6.0f * 32.0f }, { 16.0f, 16.0f }, scaleFactor, 0.0f);
	Collectable* c2 = m_Heart2->AddComponent<Collectable>();
	c2->Start();

	m_Chest = Instantiate("Chest");
	m_Chest->SetTransform({ 6.0f * 32.0f, 12.0f * 32.0f }, { 16.0f, 16.0f }, scaleFactor, 0.0f);
	Chest* chest = m_Chest->AddComponent<Chest>();
	chest->Start();

	m_Player = Instantiate("Player");
	m_Player->SetTransform({ 200.0f, 300.0f }, { 16.0f, 16.0f }, scaleFactor, 0.0f);
	PlayerControls* playerControls = m_Player->AddComponent<PlayerControls>();
	playerControls->Start(levelManager, 5.0f);

	
}