#include "PlayerControls.h"

void PlayerControls::Start()
{
	// Load sounds and audios
	m_AmbianceMusic = Audio().LoadMusic("Assets/Audios/bgm.wav");
	if (m_AmbianceMusic == 0)  Log().Print(LOG_WARNING, "ERROR LOAD MUSIC");

	m_RemoveSfx = Audio().LoadSound("Assets/Audios/Remove1.wav");
	if (m_RemoveSfx == 0)   Log().Print(LOG_WARNING, "ERROR LOAD AUDIO");

	// Load Fonts
	m_FontMerlovaz = Gfx().LoadFont("Assets/Fonts/Merlovaz.ttf", 40);
}


void PlayerControls::Update(float dt) 
{
#if _DEBUG
	if (Input().IsKeyDown(IInput::Esc))
	{
		Stel::Engine::Get().Exit();
	}
#endif

	Move();
	MouseEvents();
	AudioUpdate();
}

void PlayerControls::Move()
{
	float axiosH = Input().GetAxiosHorizontal();
	float axiosV = Input().GetAxiosVertical();
	m_Position.x += axiosH * m_Speed;
	m_Position.y += axiosV * m_Speed;
}

void PlayerControls::MouseEvents()
{
	IEvents::StelEvent stelEvent;
	if(Events().Contanis(IEvents::Quit, stelEvent))
	{
		Stel::Engine::Get().Exit();
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
	if (Input().IsKeyDown(IInput::StelKey::F))
	{
		Audio().PlaySFX(m_RemoveSfx);
	}

	if (Input().IsKeyDown(IInput::StelKey::Q))
	{
		Audio().PlayMusic(m_AmbianceMusic);
	}

	if (Input().IsKeyDown(IInput::StelKey::E))
	{
		Audio().StopMusic();
	}
}

void PlayerControls::Draw() 
{
	Gfx().SetColor({0, 0, 0, 255});
	Gfx().Clear();// TODO met at BEGIN
	StelRectF _getRect{ m_Position.x , m_Position.y , 200, 200 };
	Gfx().FillRect(_getRect, StelColor::BISQUE);

	Gfx().DrawString("TESTE", m_FontMerlovaz, { 50, 50 }, StelColor::TOMATO);
	Gfx().DrawString("TESTE 2", m_FontMerlovaz, { 300, 50 }, StelColor::AQUA);

	Gfx().Present(); // TODO met at END
}


void PlayerControls::SetPostion(StelPointF position)
{
	m_Position = position;
}

void PlayerControls::SetSpeed(float speed)
{
	m_Speed = speed;
}