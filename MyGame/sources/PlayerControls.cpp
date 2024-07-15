#include "PlayerControls.h"
#include "StelAnimation.h"


void PlayerControls::Start()
{
	// Load sounds and audios
	m_AmbianceMusic = Audio().LoadMusic("Assets/Audios/bgm.wav");
	if (m_AmbianceMusic == 0)  Log().Print(LOG_WARNING, "ERROR LOAD MUSIC");

	m_RemoveSfx = Audio().LoadSound("Assets/Audios/Remove1.wav");
	if (m_RemoveSfx == 0)   Log().Print(LOG_WARNING, "ERROR LOAD AUDIO");

	m_WalkSfx = Audio().LoadSound("Assets/Audios/sound_walk.wav");
	if (m_WalkSfx == 0)   Log().Print(LOG_WARNING, "ERROR LOAD AUDIO");


	// Load Fonts
	m_TitleFontId = Gfx().LoadFont("Assets/Fonts/Merlovaz.ttf", 30);
	m_DecrpFontId = Gfx().LoadFont("Assets/Fonts/Merlovaz.ttf", 12);
	m_Model = GetModel();
	m_Model->AddClip("walk_down"	, 0, 5, 0.1f);
	m_Model->AddClip("walk_left"	, 5, 5, 0.1f);
	m_Model->AddClip("walk_up"		, 10, 5, 0.1f);
	m_Model->AddClip("walk_right"	, 15, 5, 0.1f);


	Audio().PlayMusic(m_AmbianceMusic);
}


void PlayerControls::Update(float dt) 
{
	ChangeScene(dt);
	Move();
	MouseEvents();
	AudioUpdate();
}

void PlayerControls::ChangeScene(float dt) 
{
	if (m_ElapseTimeTouched > 0) m_ElapseTimeTouched -= dt;
	if (Input().IsKeyDown(IInput::Space) && m_ElapseTimeTouched <= 0)
	{
		World().LoadScene("MainMenu");
		
		Log().Print(LOG_INFO, "SPACE WAS PRESSED");
		m_ElapseTimeTouched = 1.0f;
	}
}

void PlayerControls::Move()
{
	float axiosH = Input().GetAxiosHorizontal();
	float axiosV = Input().GetAxiosVertical();
	m_Position.x += axiosH * m_Speed;
	m_Position.y += axiosV * m_Speed;
	
	if (m_Model != nullptr)
	{
		m_Model->SetPosition(m_Position);

		if (axiosH == 0 && axiosV == 0) 
		{
			m_Model->Stop();
			return;
		} 
		
		Audio().PlaySFX(m_WalkSfx);
		if (axiosV > 0) m_Model->Play("walk_down", true);
		else if (axiosV < 0) m_Model->Play("walk_up", true);
		else if (axiosH < 0) m_Model->Play("walk_left", true);
		else if (axiosH > 0 ) m_Model->Play("walk_right", true);
	}
}

void PlayerControls::MouseEvents()
{
	IEvents::StelEvent stelEvent;
	if(Events().Contanis(IEvents::Quit, stelEvent))
	{
		World().ExitGame();
	}

	if (Events().Contanis(IEvents::MouseButtonDown, stelEvent))
	{
		Log().Print(LOG_INFO,"Button DOWN [%d] : %d)", stelEvent.order, stelEvent.button.id);
		Log().Print(LOG_INFO, "at (%d, %d)", stelEvent.button.position.x, stelEvent.button.position.y);
	}

	if (Events().Contanis(IEvents::MouseButtonUp, stelEvent))
	{
		Log().Print(LOG_INFO, "Button UP [%d] : %d)", stelEvent.order, stelEvent.button.id);
		Log().Print(LOG_INFO, "at (%d, %d)", stelEvent.button.position.x, stelEvent.button.position.y);
	}

	if (Events().Contanis(IEvents::MouseMotion, stelEvent))
	{
		Log().Print(LOG_INFO, "Button MOVE [%d] : %d)", stelEvent.order, stelEvent.button.id);
		Log().Print(LOG_INFO, "at (%d, %d)", stelEvent.button.position.x, stelEvent.button.position.y);
	}
}

void PlayerControls::AudioUpdate()
{
	if (Input().IsKeyDown(IInput::StelKey::Z))
	{
		Audio().PlaySFX(m_RemoveSfx);
	}

	if (Input().IsKeyDown(IInput::StelKey::X))
	{
		Audio().PlayMusic(m_AmbianceMusic);
	}

	if (Input().IsKeyDown(IInput::StelKey::V))
	{
		Audio().StopMusic();
	}
}

void PlayerControls::Draw() 
{
	Gfx().DrawRect({ 0.0f, 0.0f, 800.0f, 600.0f }, StelColor::DARKDESERT);
	Gfx().DrawString("GAME SCENE", m_TitleFontId, { 15.0f,15.0f }, StelColor::AQUA);
	if(m_ElapseTimeTouched <= 0) Gfx().DrawString("- Press space to change scene - ", m_DecrpFontId, { 15.0f, 60.0f }, StelColor::DARKRED);

}


void PlayerControls::SetPostion(StelPointF position)
{
	m_Position = position;
}

void PlayerControls::SetSpeed(float speed)
{
	m_Speed = speed;
}

// JAI PAS OUBLIE DE ENLEVER ÇA
//StelSprite* PlayerControls::GetModel()
//{
//	return m_EntityParent->GetComponent<StelSprite>();
//}

//StelAtlas* PlayerControls::GetModel()
//{
//	return m_EntityParent->GetComponent<StelAtlas>();
//}

StelAnimation* PlayerControls::GetModel()
{
	return m_EntityParent->GetComponent<StelAnimation>();
}