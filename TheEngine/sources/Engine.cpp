#include "Engine.h"
#include <time.h>
//#include "SDL.h"
#include "WindowsLogger.h"
#include "FileLogger.h"

#include "SdlGfx.h"
#include "SDLInput.h"

#define MS_PER_FRAME 16.667f // TODO tester avec fraps

bool StelEngine::Engine::Init(const std::string& title, int widthScreen, int heightScreen)
{
	// Service LOG
	#if _DEBUG
		m_Logger = new WindowsLogger();
	#endif // _DEBUG
	#if _RELEASE
		m_Logger = new FileLogger();
	#endif // _RELEASE

	// Include all servers
	m_Gfx = new SdlGfx();
	m_Input = new SdlInput();
	const char* msgError = "";
	
	if (!m_Gfx->Initialize(title.c_str(), widthScreen, heightScreen, msgError))
	{
		m_Logger->Info(msgError);
		return false;
	}

	m_FPS = 0;
	m_Speed = 5;

	return true;
}

void StelEngine::Engine::Start()
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


		ProcessInput();
		Update(_deltaTime);
		Render();

		float _tempsForSleep = _startTimeCurrentFrame + MS_PER_FRAME - clock();
		// GAG for the current frame
		if (_tempsForSleep > 0) Sleep(_tempsForSleep);

		
		_endTimeLastFrame = _startTimeCurrentFrame;
	}
	Shutdown();
}

void StelEngine::Engine::ProcessInput()
{
	float axiosH = m_Input->GetAxiosHorizontal();
	float axiosV = m_Input->GetAxiosVertical();
	m_Position->x += axiosH * m_Speed;
	m_Position->y += axiosV * m_Speed;


	SDL_Event _event;
	while (SDL_PollEvent(&_event))
	{
		switch (_event.type) 
		{
		case SDL_QUIT:
			Exit();
			break;
		case SDL_MOUSEBUTTONDOWN:
			SDL_MouseButtonEvent _buttonDown = _event.button;
			m_Logger->Info("Button down : %d)", _buttonDown.button);
			m_Logger->Info("at (%d, %d)", _buttonDown.x, _buttonDown.y);
			break;
		case SDL_MOUSEBUTTONUP:
			SDL_MouseButtonEvent _buttonUp = _event.button;
			m_Logger->Info("Button up : %d)", _buttonUp.button);
			m_Logger->Info("at (%d, %d)", _buttonUp.x, _buttonUp.y);
			break;
		case SDL_MOUSEMOTION:
			SDL_MouseMotionEvent _motion = _event.motion;
			m_Logger->Info("at (%d, %d)", _motion.x, _motion.y);
			break;
		default:
			break;
		}
	}
}

void StelEngine::Engine::Update(float deltaTime)
{
	m_Input->Update(deltaTime);
}

void StelEngine::Engine::Render()
{
	m_Gfx->SetColor({ 0, 0, 0, 255 });
	m_Gfx->Clear();// TODO met � BEGIN
	StelRectF _getRect{ m_Position->x , m_Position->y , 200, 200 };
	m_Gfx->FillRect(_getRect, StelColor::Red);
	m_Gfx->Present(); // TODO met � END
}

void StelEngine::Engine::Shutdown()
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

void StelEngine::Engine::Exit()
{
	m_isRunning = false;
}