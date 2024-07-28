#include "GameScene.h"
#include "StelEngine.h"
#include "PlayerControls.h"
#include "StelAnimation.h"
#include "LevelManager.h"
#include "Collectable.h"
#include "Chest.h"
#include "Door.h"
#include "Box.h"


void GameScene::Load()
{
	float scaleFactor = 2.0f;
	StelPointF size = { 16.0f , 16.0f };
	float mult = scaleFactor * size.x;
	char* spriteSheet = "Assets/adv_lolo_map.png";


	m_Level  = Instantiate("Level");
	m_Level->SetTransform(StelPointF::Zero(), size, scaleFactor, 0.0f);

	LevelManager* levelManager = m_Level->AddComponent<LevelManager>();
	levelManager->Start();

	m_Heart1 = Instantiate("Item1");
	m_Heart1->SetTransform({ 6.0f * mult, 3.0f * mult }, size, scaleFactor, 0.0f);
	Collectable* c1 = m_Heart1->AddComponent<Collectable>();
	c1->Start(spriteSheet, {1, 3});

	m_Heart2 = Instantiate("Item2");
	m_Heart2->SetTransform({ 12.0f * mult, 6.0f * mult }, size, scaleFactor, 0.0f);
	Collectable* c2 = m_Heart2->AddComponent<Collectable>();
	c2->Start(spriteSheet, { 1, 3 });

	m_Chest = Instantiate("Chest");
	m_Chest->SetTransform({ 6.0f * mult, 12.0f * mult }, size, scaleFactor, 0.0f);
	Chest* chest = m_Chest->AddComponent<Chest>();
	c1->OnItem.AddListener(chest);
	c2->OnItem.AddListener(chest);
	chest->Start(spriteSheet, 2);

	m_Door = Instantiate("Door");
	m_Door->SetTransform({ 8.0f * mult, 1.0f * mult }, size, scaleFactor, 0.0f);
	Door* door = m_Door->AddComponent<Door>();
	chest->OnGetPearl.AddListener(door);
	door->Start(spriteSheet, "Game");

	m_Box = Instantiate("Box");
	m_Box->SetTransform({ 4.0f * mult, 7.0f * mult }, size, scaleFactor, 0.0f);
	Box* box = m_Box->AddComponent<Box>();
    //box->OnGetPearl.AddListener(door);
	box->Start(spriteSheet, {0, 3}, levelManager);


	m_Player = Instantiate("Player");
	m_Player->SetTransform({ 6.0f * mult, 9.0f * mult }, size, scaleFactor, 0.0f);
	PlayerControls* playerControls = m_Player->AddComponent<PlayerControls>();
	playerControls->Start(levelManager, 5.0f);

	
}