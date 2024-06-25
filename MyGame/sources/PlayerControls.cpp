#include "PlayerControls.h"

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
	IEvents::StelEvent stelEvent = Stel::Engine::Get().GetEventService().PullEvent();
	switch (stelEvent.type)
	{
	case IEvents::Quit:
		Stel::Engine::Get().Exit();
		break;
	case IEvents::MouseButtonDown:
		Stel::Engine::Get().GetLoggerService().Info("Button DOWN : %d)", stelEvent.button.id);
		Log().Info("at (%d, %d)", stelEvent.button.position.x, stelEvent.button.position.y);
		break;
	case IEvents::MouseButtonUp:
		Log().Info("Button UP : %d)", stelEvent.button.id);
		Log().Info("at (%d, %d)", stelEvent.button.position.x, stelEvent.button.position.y);
		break;
	case IEvents::MouseMotion:
		Log().Info("Button MOVE:)");
		Log().Info("at (%d, %d)", stelEvent.button.position.x, stelEvent.button.position.y);
		break;
	default:
		break;
	}
}

void PlayerControls::AudioUpdate()
{
	if (Input().IsKeyDown(IInput::StelKey::F))
	{
		//audio->PlaySFX(m_RemoveSfx);
	}

	if (Input().IsKeyDown(IInput::StelKey::Q))
	{
		//audio->PlayMusic(m_AmbianceMusic);
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

	//Gfx().DrawString("TESTE", m_FontMerlovaz, { 50, 50 }, StelColor::TOMATO);
	//Gfx().DrawString("TESTE 2", m_FontMerlovaz, { 300, 50 }, StelColor::AQUA);

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