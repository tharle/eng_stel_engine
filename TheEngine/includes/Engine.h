#pragma once
#include <string>
#include "IInput.h"
#include "ILogger.h"
#include "IGfx.h"

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
		bool m_IsInit;
		bool m_isRunning;
		int m_FPS;
		float m_Speed;

		// testing moving square
		StelPointF* m_Position;

		ILogger* m_Logger;
		IInput* m_Input;
		IGfx* m_Gfx;

	};
}