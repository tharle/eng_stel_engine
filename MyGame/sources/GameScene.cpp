#include "GameScene.h"
#include "StelEngine.h"
#include "PlayerControls.h"
#include "StelAnimation.h"
#include "LevelManager.h"
#include "Collectable.h"
#include "Chest.h"
#include "Door.h"
#include "Box.h"
#include "Enemy.h"

void GameScene::Load()
{
	float scaleFactor = 2.0f;
	StelPointF size = { 16.0f , 16.0f };
	float mult = scaleFactor * size.x;
	char* spriteSheet = "Assets/adv_lolo_map.png";
	char* spriteSheetMisc = "Assets/adv_lolo_misc.png";


	StelEntity* level  = Instantiate("Level");
	level->SetTransform(StelPointF::Zero(), size, scaleFactor, 0.0f);
	LevelManager* levelManager = level->AddComponent<LevelManager>();
	levelManager->Start();

	StelEntity* heart1 = Instantiate("Item1");
	heart1->SetTransform({ 6.0f * mult, 3.0f * mult }, size, scaleFactor, 0.0f);
	Collectable* c1 = heart1->AddComponent<Collectable>();
	c1->Start(spriteSheet, {1, 3});

	StelEntity* heart2 = Instantiate("Item2");
	heart2->SetTransform({ 12.0f * mult, 6.0f * mult }, size, scaleFactor, 0.0f);
	Collectable* c2 = heart2->AddComponent<Collectable>();
	c2->Start(spriteSheet, { 1, 3 });

	StelEntity* chestEnitty = Instantiate("Chest");
	chestEnitty->SetTransform({ 6.0f * mult, 12.0f * mult }, size, scaleFactor, 0.0f);
	Chest* chest = chestEnitty->AddComponent<Chest>();
	c1->OnItem.AddListener(chest);
	c2->OnItem.AddListener(chest);
	chest->Start(spriteSheet, 2);

	StelEntity* doorEntity = Instantiate("Door");
	doorEntity->SetTransform({ 8.0f * mult, 1.0f * mult }, size, scaleFactor, 0.0f);
	Door* door = doorEntity->AddComponent<Door>();
	chest->OnGetPearl.AddListener(door);
	door->Start(spriteSheet, "Game");

	StelEntity* player = Instantiate("Player");
	player->SetTransform({ 6.0f * mult, 9.0f * mult }, size, scaleFactor, 0.0f);
	PlayerControls* playerControls = player->AddComponent<PlayerControls>();
	playerControls->Start(levelManager, 5.0f);

	StelEntity* dragBox = Instantiate("Box");
	dragBox->SetTransform({ 6.0f * mult, 7.0f * mult }, size, scaleFactor, 0.0f);
	dragBox->AddComponent<Box>()->Start(levelManager);
	StelAtlas* boxModel = dragBox->AddComponent<StelAtlas>();
	boxModel->Init(spriteSheet);
	StelPointI sizeInt = StelPointI::FromFloat(size.x, size.y);
	boxModel->AddFrame({ 0, 3 * sizeInt.y,sizeInt.x, sizeInt.y });
	boxModel->SetFrame(0);
	boxModel->Start();

	StelEntity* greenWormEntity = Instantiate("Green Worm");
	greenWormEntity->SetTransform({ 3.0f * mult, 6.0f * mult }, size, scaleFactor, 0.0f);
	Enemy* greenWorm = greenWormEntity->AddComponent<Enemy>();
	chest->OnOpenChest.AddListener(greenWorm);
	chest->OnGetPearl.AddListener(greenWorm);
	greenWorm->Start(spriteSheetMisc);
	Box* greenWormBox = greenWormEntity->AddComponent<Box>();
	greenWormBox->SetDraggable(false);
	greenWormBox->Start(levelManager);
	playerControls->OnMove.AddListener(greenWorm);

	
}