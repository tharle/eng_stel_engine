#include "MainMenuManager.h"

void MainMenuManager::Start()
{
	m_TitleFontId = Gfx().LoadFont("Assets/Fonts/Merlovaz.ttf", 90);
	m_DecrpFontId = Gfx().LoadFont("Assets/Fonts/Merlovaz.ttf", 25);
}

void MainMenuManager::Update(float dt)
{
	if (m_ElapseTimeTouched > 0) m_ElapseTimeTouched -= dt;
	if (Input().IsKeyDown(IInput::Space) && m_ElapseTimeTouched <= 0)
	{
		Stel::Engine::Get().GetWorld().LoadScene("Game");
		Log().Print(LOG_INFO, "SPACE WAS PRESSED");
		m_ElapseTimeTouched = 1.0f;
	}
}

void MainMenuManager::Draw()
{
	Gfx().DrawString("MAIN MENU", m_TitleFontId, { 100.0f, 210.0f }, StelColor::AQUA);
	Gfx().DrawString("- Press space to change scene - ", m_DecrpFontId, { 230.0f, 400.0f }, StelColor::AZURE);
}