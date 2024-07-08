#include "MainMenuScene.h"
#include "StelEngine.h"
#include "MainMenuManager.h"

MainMenuScene::~MainMenuScene()
{
	/*if (m_MainMenuEntity != nullptr)
	{
		delete m_MainMenuEntity;
		m_MainMenuEntity = nullptr;
	}*/
}

void MainMenuScene::Load() 
{
	m_MainMenuEntity = Stel::Engine::Get().GetWorld().Create("MainMenu");
	m_MainMenuEntity->AddComponent<MainMenuManager>()->Start();
}