#include "PlayerControls.h"
PlayerControls::PlayerControls(StelEntity* parent, StelPointF initPos, float speed) : 
	StelComponent(parent),
	m_Position(initPos),
	m_Speed(speed)
{

}

void PlayerControls::Update(float dt) 
{
	IInput* input =  &Stel::Engine::Get().GetInputService();
	ILogger* log =  &Stel::Engine::Get().GetLoggerService();
	IAudio* audio = &Stel::Engine::Get().GetAudioService();

	float axiosH = input->GetAxiosHorizontal();
	float axiosV = input->GetAxiosVertical();
	m_Position.x += axiosH * m_Speed;
	m_Position.y += axiosV * m_Speed;

#if _DEBUG
	if (input->IsKeyDown(IInput::Esc))
	{
		Stel::Engine::Get().Exit();
	}
#endif

	if (input->IsKeyDown(IInput::StelKey::F))
	{
		//audio->PlaySFX(m_RemoveSfx);
	}

	if (input->IsKeyDown(IInput::StelKey::Q))
	{
		//audio->PlayMusic(m_AmbianceMusic);
	}

	if (input->IsKeyDown(IInput::StelKey::E))
	{
		audio->StopMusic();
	}

	IEvents::StelEvent stelEvent = Stel::Engine::Get().GetEventService().PullEvent();
	switch (stelEvent.type)
	{
	case IEvents::Quit:
		Stel::Engine::Get().Exit();
		break;
	case IEvents::MouseButtonDown:
		Stel::Engine::Get().GetLoggerService().Info("Button DOWN : %d)", stelEvent.button.id);
		log->Info("at (%d, %d)", stelEvent.button.position.x, stelEvent.button.position.y);
		break;
	case IEvents::MouseButtonUp:
		log->Info("Button UP : %d)", stelEvent.button.id);
		log->Info("at (%d, %d)", stelEvent.button.position.x, stelEvent.button.position.y);
		break;
	case IEvents::MouseMotion:
		log->Info("Button MOVE:)");
		log->Info("at (%d, %d)", stelEvent.button.position.x, stelEvent.button.position.y);
		break;
	default:
		break;
	}
}

void PlayerControls::Draw() 
{
	IGfx* gfx = &Stel::Engine::Get().GetGfxService();
	gfx->SetColor({ 0, 0, 0, 255 });
	gfx->Clear();// TODO met at BEGIN
	StelRectF _getRect{ m_Position.x , m_Position.y , 200, 200 };
	gfx->FillRect(_getRect, StelColor::BISQUE);

	//gfx->DrawString("TESTE", m_FontMerlovaz, { 50, 50 }, StelColor::TOMATO);
	//gfx->DrawString("TESTE 2", m_FontMerlovaz, { 300, 50 }, StelColor::AQUA);

	gfx->Present(); // TODO met at END
}


void PlayerControls::SetPostion(StelPointF position)
{
	m_Position = position;
}

void PlayerControls::SetSpeed(float speed)
{
	m_Speed = speed;
}