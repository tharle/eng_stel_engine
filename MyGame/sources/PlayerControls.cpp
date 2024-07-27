#include "PlayerControls.h"
#include "StelAnimation.h"
#include "LevelManager.h"


void PlayerControls::Start(LevelManager* currentLevel) 
{
	StelComponent::Start();

	m_CurrentLevel = currentLevel;

	// Load sounds and audios
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

	float offset = 4.0f;
	m_Collider = { -offset,-offset, - offset , - offset };
}


void PlayerControls::Update(float dt) 
{
	Move(dt);
	MouseEvents();
	AudioUpdate();
}

void PlayerControls::Move(float dt)
{
 
	// TODO change for Transform in entity
	float axiosH = Input().GetAxiosHorizontal();
	float axiosV = Input().GetAxiosVertical();
	m_Position.x += axiosH * m_Speed;
	m_Position.y += axiosV * m_Speed;

	StelRectF collider = {
		m_Position.x - m_Collider.x,
		m_Position.y - m_Collider.y,
		m_Size.x + m_Collider.x,
		m_Size.y + m_Collider.y
	};

	if (m_CurrentLevel->IsColliding(collider.Resize(m_ScaleFactor)))
	{
		m_Position.x -= axiosH * m_Speed;
		m_Position.y -= axiosV * m_Speed;
	}
	
	if (m_Model != nullptr)
	{
		m_Model->SetPosition(m_Position);

		if (axiosH == 0 && axiosV == 0) 
		{
			m_Model->Stop();
			return;
		} 
		
		if (m_CooldownWalkSound <= 0)
		{
			m_CooldownWalkSound = COOLDOWN_WALK_SOUND;
			Audio().PlaySFX(m_WalkSfx);
		}
		else m_CooldownWalkSound -= dt;
		
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
}

void PlayerControls::Draw() 
{
	Gfx().DrawRect({ 0.0f, 480.0f, 512.0f, 32.0f }, StelColor::WHITE); // down UI
	Gfx().DrawRect({ 448.0f, 0.0f, 64.0f, 480.0f }, StelColor::WHITE); // Right side UI
	//Gfx().DrawString("GAME SCENE", m_TitleFontId, { 15.0f,15.0f }, StelColor::AQUA);
	//if(m_CooldownChangeScene <= 0) Gfx().DrawString("- Press space to change scene - ", m_DecrpFontId, { 32.0f, 488.0f }, StelColor::DARKRED);
}


void PlayerControls::SetPostion(StelPointF position)
{
	m_Position = position;
}

void PlayerControls::SetSpeed(float speed)
{
	m_Speed = speed;
}

void PlayerControls::SetSize(StelPointF size, float scaleFactor)
{
	m_Size = size;
	m_ScaleFactor = scaleFactor;
}

StelAnimation* PlayerControls::GetModel()
{
	return m_EntityParent->GetComponent<StelAnimation>();
}


