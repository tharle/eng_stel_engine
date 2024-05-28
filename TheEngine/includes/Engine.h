#pragma once
#include <string>
#include "IInput.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Point;

namespace StelEngine
{
	class Engine final
	{
	public :
		bool Init(const std::string& title, int widthScreen, int heightScren);
		void Start();
		const IInput* GetInput() {return m_Input;};
	private:
		void ProcessInput();
		void Update(float deltaTime);
		void Render();
		void Shutdown();
		void Exit();
	private:
		SDL_Window* m_Window;
		SDL_Renderer* m_Renderer;
		SDL_Point* m_Position;
		bool m_IsInit;
		bool m_isRunning;
		IInput* m_Input;
	};
}