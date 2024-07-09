#include "GameScene.h"
#include "StelEngine.h"
#include "PlayerControls.h"
#include "StelAnimation.h"


void GameScene::Load()
{
	m_Player = Stel::Engine::Get().GetWorld().Create("Player");

	// JAI PAS OUBLIE DE ENLEVER ÇA
	/*StelSprite* model = m_Player->AddComponent<StelSprite>();
	model->Init("Assets/adv_lolo_char.png", { 0, 0, 15, 15 }, { 200.0f, 200.0f, 64.0f, 64.0f })->Start();*/
	/*StelAtlas* model = m_Player->AddComponent<StelAtlas>();
	model->Init("Assets/adv_lolo_char.png", {64, 64});*/
	StelAnimation* model = m_Player->AddComponent<StelAnimation>();
	model->Init("Assets/adv_lolo_char.png", { 64, 64 });
	model->Start();
	model->AddAnimationFrames(5, { 0, 0 }, {16, 16});
	model->AddAnimationFrames(5, { 0, 16 }, {16, 16});
	model->AddAnimationFrames(5, { 0, 32 }, {16, 16});
	model->AddAnimationFrames(5, { 0, 48 }, {16, 16});

	PlayerControls* playerControls = m_Player->AddComponent<PlayerControls>();
	playerControls->SetPostion({ 400.0f, 400.0f });
	playerControls->SetSpeed(15.0f);
	playerControls->Start();


	
}