#include "MainMenuManager.h"

void MainMenuManager::Start()
{
	m_TitleFontId = Gfx().LoadFont("Assets/Fonts/Merlovaz.ttf", 90);
	m_DecrpFontId = Gfx().LoadFont("Assets/Fonts/Merlovaz.ttf", 25);
}

void MainMenuManager::Update(float dt)
{
	if (Input().IsKeyDown(IInput::Space))
	{
		Stel::Engine::Get().GetWorld().LoadScene("Game");
		Log().Print(LOG_INFO, "SPACE WAS PRESSED");
	}
}

void MainMenuManager::Draw()
{
	Gfx().DrawString("MAIN MENU", m_TitleFontId, { 100.0f, 210.0f }, StelColor::AQUA);
	Gfx().DrawString("- Press space to change scene - ", m_DecrpFontId, { 230.0f, 400.0f }, StelColor::AZURE);
	Gfx().Present(); // TODO met at END
}