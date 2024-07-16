#include "StelEngine.h"
#include <time.h>
#include "WindowsLogger.h"
#include "FileLogger.h"

#include "SdlGfx.h"
#include "SdlInput.h"
#include "SdlEvents.h"
#include "SdlAudio.h"

#include "StelWorldService.h"

#define MS_PER_FRAME 16.667f // TODO tester avec fraps

bool Stel::Engine::Init(const std::string& title, StelPointI screenDimension)
{
	m_ScreenDimension = screenDimension;
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
	if (!m_Gfx->Initialize(title.c_str(), m_ScreenDimension.x, m_ScreenDimension.y, msgError))
	{
		m_Logger->Print(ERROR, msgError);
		return false;
	}

	m_FPS = 0;

	// Load World
	m_World = new StelWorld();

	m_IsInit = true;

	return true;
}

void Stel::Engine::Start()
{
	if (!m_IsInit)
	{
		if (!Init("Legends of Stel", m_ScreenDimension))
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
		float _deltaTime = (_startTimeCurrentFrame - _endTimeLastFrame) * 0.001f;

		_elapseTime += _deltaTime;
		m_FPS++;
		if (_elapseTime >= 1) 
		{
			//m_Logger->Print(LOG_INFO, "FPS %d", m_FPS);
			_elapseTime = 0;
			m_FPS = 0;
		}
		m_Events->Update();
		ProcessInput();
		Update(_deltaTime);
		Render();

		float _tempsForSleep = _startTimeCurrentFrame + MS_PER_FRAME - clock();
		// GAG for the current frame
		if (_tempsForSleep > 0) Sleep(long(_tempsForSleep));

		
		_endTimeLastFrame = _startTimeCurrentFrame;
	}
	Shutdown();
}

void Stel::Engine::ProcessInput()
{
	#if _DEBUG
		if (m_Input->IsKeyDown(IInput::Esc))
		{
			Exit();
		}
	#endif
		IEvents::StelEvent stelEvent;
		if (m_Events->Contanis(IEvents::Quit, stelEvent)) 
		{
			Exit();
		}
}

void Stel::Engine::Update(float deltaTime)
{
	m_Input->Update(deltaTime);
	m_World->Update(deltaTime);
}

void Stel::Engine::Render()
{
	//m_Gfx->SetColor({ 0, 0, 0, 255 });
	m_Gfx->Clear();// TODO met at BEGIN
	m_World->Draw();
	m_Gfx->SetColor({ 0, 0, 0, 255 });
	m_Gfx->Present(); // TODO met at END
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

	if (m_Events != nullptr)
	{
		delete m_Events;
		m_Events = nullptr;
	}

	if (m_Logger != nullptr) 
	{
		delete m_Logger;
		m_Logger = nullptr;
	}

	if (m_Audio != nullptr)
	{
		delete m_Audio;
		m_Audio = nullptr;
	}

	if (m_World != nullptr)
	{
		delete m_World;
		m_World = nullptr;
	}

}

void Stel::Engine::Exit()
{
	m_isRunning = false;
}