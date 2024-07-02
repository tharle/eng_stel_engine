#include "MainMenuScene.h"
#include "StelEngine.h"
#include "PlayerControls.h"

void MainMenuScene::Load() 
{
	m_Player = Stel::Engine::Get().GetWorld().Create("Player");
	m_PlayerControls = m_Player->AddComponent<PlayerControls>();
	m_PlayerControls->Start();
	m_PlayerControls->SetPostion({ 400.0f, 400.0f });
	m_PlayerControls->SetSpeed(15.0f);

}