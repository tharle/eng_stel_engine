#include "Engine.h"
#include <time.h>
#include "SDL.h"
#include "SDLInput.h"

bool StelEngine::Engine::Init(const std::string& title, int widthScreen, int heightScreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING != 0))
	{
		SDL_Log(SDL_GetError());
		return false;
	}
	int _x = SDL_WINDOWPOS_CENTERED;
	int _y = SDL_WINDOWPOS_CENTERED;
	Uint32 _flag = SDL_WINDOW_TOOLTIP;

	m_Window = SDL_CreateWindow(title.c_str(), _x, _y, widthScreen, heightScreen, _flag);
	if (!m_Window)
	{
		SDL_Log(SDL_GetError());
		return false;
	}

	_flag = SDL_RENDERER_ACCELERATED;
	m_Renderer = SDL_CreateRenderer(m_Window, -1, _flag);
	if (!m_Renderer)
	{
		SDL_Log(SDL_GetError());
		return false;
	}

	m_Input = new SDLInput();

	return true;
}

void StelEngine::Engine::Start()
{
	if (!m_IsInit)
	{
		_x = 200;
		_y = 200;
		if (!Init("Legends of Stel", 800, 600))
		{
			return;
		}
	}

	m_isRunning = true;
	clock_t _end = clock();
	int _frames = 0;
	float _elapseTimeIn30fps = 0;
	while (m_isRunning)
	{
		if (_frames > 60) 
		{
			float sleepTime = 1 - _elapseTimeIn30fps;
			SDL_Delay(sleepTime);
			_elapseTimeIn30fps = 0;
			_frames = 0;
			continue;
		}

		_frames++;
		const clock_t _start = clock();
		float _deltaTime = (_start - _end) * 0.001f;
		_elapseTimeIn30fps += _deltaTime;
		ProcessInput();
		Update(_deltaTime);
		Render();
		_end = _start;
	}
	Shutdown();
}

void StelEngine::Engine::ProcessInput()
{
	m_Input->Update();
	SDL_Event _event;
	const unsigned char* _keyStates = SDL_GetKeyboardState(nullptr);
	if (_keyStates[SDL_SCANCODE_LEFT])
	{
		SDL_Log("LEFT");
		_x--;
	}

	if (_keyStates[SDL_SCANCODE_RIGHT])
	{
		SDL_Log("RIGHT");
		_x++;
	}

	if (_keyStates[SDL_SCANCODE_DOWN])
	{
		SDL_Log("DOWN");
		_y++;
	}

	if (_keyStates[SDL_SCANCODE_UP])
	{
		SDL_Log("UP");
		_y--;
	}



	while (SDL_PollEvent(&_event))
	{
		switch (_event.type) 
		{
		case SDL_QUIT:
			Exit();
			break;
		case SDL_MOUSEBUTTONDOWN:
			SDL_MouseButtonEvent _buttonDown = _event.button;
			//SDL_Log("Button down : %d)", _buttonDown.button);
			//SDL_Log("at (%d, %d)", _buttonDown.x, _buttonDown.y);
			break;
		case SDL_MOUSEBUTTONUP:
			SDL_MouseButtonEvent _buttonUp = _event.button;
			//SDL_Log("Button up : %d)", _buttonUp.button);
			//SDL_Log("at (%d, %d)", _buttonUp.x, _buttonUp.y);
			break;
		case SDL_MOUSEMOTION:
			SDL_MouseMotionEvent _motion = _event.motion;
			//SDL_Log("at (%d, %d)", _motion.x, _motion.y);
			break;
		default:
			break;
		}
	}
}

void StelEngine::Engine::Update(float deltaTime)
{

}

void StelEngine::Engine::Render()
{
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_Renderer);
	SDL_SetRenderDrawColor(m_Renderer, 255, 0, 0, 255);
	SDL_Rect _getRect;
	_getRect.x = _x;
	_getRect.y = _y;
	_getRect.w = 200;
	_getRect.h = 200;
	SDL_RenderFillRect(m_Renderer, &_getRect);
	SDL_RenderPresent(m_Renderer);

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