#include "PlayerControls.h"
#include "StelAtlas.h"

void PlayerControls::Start()
{
	// Load sounds and audios
	m_AmbianceMusic = Audio().LoadMusic("Assets/Audios/bgm.wav");
	if (m_AmbianceMusic == 0)  Log().Print(LOG_WARNING, "ERROR LOAD MUSIC");

	m_RemoveSfx = Audio().LoadSound("Assets/Audios/Remove1.wav");
	if (m_RemoveSfx == 0)   Log().Print(LOG_WARNING, "ERROR LOAD AUDIO");

	// Load Fonts
	m_TitleFontId = Gfx().LoadFont("Assets/Fonts/Merlovaz.ttf", 30);
	m_DecrpFontId = Gfx().LoadFont("Assets/Fonts/Merlovaz.ttf", 12);
	m_Model = GetModel();
	//m_Model.
	m_Model->AddFrame(m_NameFrames[0], {0, 0, 15, 15});
	m_Model->AddFrame(m_NameFrames[1], { 16, 0, 15, 15 });
	m_Model->AddFrame(m_NameFrames[2], { 32, 0, 15, 15 });
	m_Model->AddFrame(m_NameFrames[3], { 48, 0, 15, 15 });
	m_Model->AddFrame(m_NameFrames[4], { 64, 0, 15, 15 });
	m_CurrentFrame = 0;
	m_Model->SetFrame(m_NameFrames[m_CurrentFrame]);
}


void PlayerControls::Update(float dt) 
{
	ChangeScene(dt);
	Move();
	MouseEvents();
	AudioUpdate();
	NextFrame();
}

void PlayerControls::ChangeScene(float dt) 
{
	if (m_ElapseTimeTouched > 0) m_ElapseTimeTouched -= dt;
	if (Input().IsKeyDown(IInput::Space) && m_ElapseTimeTouched <= 0)
	{
		Stel::Engine::Get().GetWorld().LoadScene("MainMenu");
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

	StelSprite* model = GetModel();
	if(model != nullptr) model->SetPosition(m_Position);
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

void PlayerControls::NextFrame() 
{
	if (Input().IsKeyDown(IInput::Q))
	{
		m_CurrentFrame++;
		m_CurrentFrame %= m_NameFrames.size();
		m_Model->SetFrame(m_NameFrames[m_CurrentFrame]);
	}
}

void PlayerControls::Draw() 
{
	//StelRectF _getRect{ m_Position.x , m_Position.y , 200.0f, 200.0f };
	//Gfx().FillRect(_getRect, StelColor::BISQUE);

	Gfx().DrawString("GAME SCENE", m_TitleFontId, { 15.0f,15.0f }, StelColor::TOMATO);
	if(m_ElapseTimeTouched <= 0) Gfx().DrawString("- Press space to change scene - ", m_DecrpFontId, { 15.0f, 60.0f }, StelColor::AZURE);
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

StelAtlas* PlayerControls::GetModel()
{
	return m_EntityParent->GetComponent<StelAtlas>();
}