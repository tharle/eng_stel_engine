#include "MainMenuScene.h"
#include "StelEngine.h"
#include "MainMenuManager.h"

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::Load() 
{
	m_MainMenuEntity = Stel::Engine::Get().GetWorld().Create("MainMenu");
	m_MainMenuEntity->AddComponent<MainMenuManager>()->Start();
}