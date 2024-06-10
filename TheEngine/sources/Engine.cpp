#include "Engine.h"
#include <time.h>
#include "SDL.h"
#include "SDLInput.h"
#include "WindowsLogger.h"

// Library effective with Windows
#include <windows.h>
// Library effective with Linux
//#include <unistd.h>
#define MS_PER_FRAME 16.667f // TODO tester avec fraps

bool StelEngine::Engine::Init(const std::string& title, int widthScreen, int heightScreen)
{


	if (SDL_Init(SDL_INIT_EVERYTHING != 0))
	{
		m_Logger->Info(SDL_GetError());
		return false;
	}
	int _x = SDL_WINDOWPOS_CENTERED;
	int _y = SDL_WINDOWPOS_CENTERED;
	Uint32 _flag = SDL_WINDOW_TOOLTIP;

	m_Window = SDL_CreateWindow(title.c_str(), _x, _y, widthScreen, heightScreen, _flag);
	if (!m_Window)
	{
		m_Logger->Info(SDL_GetError());
		return false;
	}

	_flag = SDL_RENDERER_ACCELERATED;
	m_Renderer = SDL_CreateRenderer(m_Window, -1, _flag);
	if (!m_Renderer)
	{
		m_Logger->Info(SDL_GetError());
		return false;
	}

	m_Logger = new WindowsLogger();
	// Include all servers
	m_Input = new SdlInput();


	m_FPS = 0;
	m_Speed = 5;

	return true;
}

void StelEngine::Engine::Start()
{
	m_Position = new SDL_FPoint{200.0f, 200.0f};
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
	/*m_Logger->Info("axiosH %f", axiosH);
	m_Logger->Info("axiosV %f", axiosV);
	m_Logger->Info("Speed %f", m_Speed);*/
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
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_Renderer); // TODO met à BEGIN
	SDL_SetRenderDrawColor(m_Renderer, 255, 0, 0, 255);
	SDL_Rect _getRect;
	_getRect.x = m_Position->x;
	_getRect.y = m_Position->y;
	_getRect.w = 200;
	_getRect.h = 200;
	SDL_RenderFillRect(m_Renderer, &_getRect);
	SDL_RenderPresent(m_Renderer); // TODO met à END

	//SDL_Log(_x);
}

void StelEngine::Engine::Shutdown()
{
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

void StelEngine::Engine::Exit()
{
	m_isRunning = false;
}