#include "StelEngine.h"
#include <time.h>
#include "WindowsLogger.h"
#include "FileLogger.h"

#include "SdlGfx.h"
#include "SdlInput.h"
#include "SdlEvents.h";
#include "SdlAudio.h"

#include "StelWorldService.h"

#define MS_PER_FRAME 16.667f // TODO tester avec fraps

bool Stel::Engine::Init(const std::string& title, int widthScreen, int heightScreen)
{
	// Service LOG
	#if _DEBUG
		m_Logger = new WindowsLogger(); // _DEBUG
	#else
		m_Logger = new FileLogger();
	#endif // _RELEASE

	// Include all servers
	m_Gfx = new SdlGfx();
	m_Events = new SdlEvents();
	m_Input = new SdlInput();
	m_Audio = new SdlAudio();

	const char* msgError = "";
	if (!m_Gfx->Initialize(title.c_str(), widthScreen, heightScreen, msgError))
	{
		m_Logger->Info(msgError);
		return false;
	}

	m_FPS = 0;
	//m_Speed = 5;

	//// LOAD Fonts
	//m_FontMerlovaz = m_Gfx->LoadFont("Assets/Fonts/Merlovaz.ttf", 40, msgError);
	//if (m_FontMerlovaz == 0)
	//{
	//	m_Logger->Info(msgError);
	//}

	// Load sounds and audios
	m_AmbianceMusic = m_Audio->LoadMusic("Assets/Audios/bgm.wav");
	if (m_AmbianceMusic == 0)  m_Logger->Info("ERROR LOAD MUSIC");

	m_RemoveSfx = m_Audio->LoadSound("Assets/Audios/Remove1.wav");
	if (m_RemoveSfx == 0)  m_Logger->Info("ERROR LOAD AUDIO");

	// Load World
	m_World = new StelWorldService();

	m_IsInit = true;

	return true;
}

void Stel::Engine::Start()
{
	m_Position = new StelPointF{200.0f, 200.0f};
	if (!m_IsInit)
	{
		if (!Init("Legends of Stel", 800, 600))
		{
			return;
		}
	}

	m_isRunning = true;
	clock_t _endTimeLastFrame = clock();
	float _elapseTime = 0;
	while (m_isRunning)
	{
		const clock_t _startTimeCurrentFrame = clock();
		float _deltaTime = (_startTimeCurrentFrame - _endTimeLastFrame) * 0.001;

		_elapseTime += _deltaTime;
		m_FPS++;
		if (_elapseTime >= 1) 
		{
			m_Logger->Info("FPS %d", m_FPS);
			_elapseTime = 0;
			m_FPS = 0;
		}
		m_Events->Update();
		Update(_deltaTime);
		Render();

		float _tempsForSleep = _startTimeCurrentFrame + MS_PER_FRAME - clock();
		// GAG for the current frame
		if (_tempsForSleep > 0) Sleep(_tempsForSleep);

		
		_endTimeLastFrame = _startTimeCurrentFrame;
	}
	Shutdown();
}

void Stel::Engine::ProcessInput()
{
	/*
	#if _DEBUG
	if(m_Input->IsKeyDown(IInput::Esc))
	{
		Exit();
	}
	#endif

	if (m_Input->IsKeyDown(IInput::StelKey::F)) 
	{
		m_Audio->PlaySFX(m_RemoveSfx);
	}

	if (m_Input->IsKeyDown(IInput::StelKey::Q))
	{
		m_Audio->PlayMusic(m_AmbianceMusic);
	}

	if (m_Input->IsKeyDown(IInput::StelKey::E))
	{
		m_Audio->StopMusic();
	}
	*/
}

void Stel::Engine::Update(float deltaTime)
{
	m_Input->Update(deltaTime);
	m_World->Update(deltaTime);
}

void Stel::Engine::Render()
{
	m_World->Draw();

	//m_Gfx->SetColor({ 0, 0, 0, 255 });
	//m_Gfx->Clear();// TODO met � BEGIN
	//StelRectF _getRect{ m_Position->x , m_Position->y , 200, 200 };
	//m_Gfx->FillRect(_getRect, StelColor::DARKRED);

	//m_Gfx->DrawString("TESTE", m_FontMerlovaz, { 50, 50 }, StelColor::TOMATO);
	//m_Gfx->DrawString("TESTE 2", m_FontMerlovaz, { 300, 50 }, StelColor::AQUA);

	//m_Gfx->Present(); // TODO met � END
}

void Stel::Engine::Shutdown()
{
	if (m_Gfx != nullptr) 
	{
		m_Gfx->Shutdown();
		delete m_Gfx;
		m_Gfx = nullptr;
	}

	if (m_Input != nullptr) 
	{
		delete m_Input;
		m_Input = nullptr;
	}

	if (m_Logger != nullptr) 
	{
		delete m_Logger;
		m_Logger = nullptr;
	}

	if (m_Position != nullptr) 
	{
		delete m_Position;
		m_Position = nullptr;
	}
}

void Stel::Engine::Exit()
{
	m_isRunning = false;
}