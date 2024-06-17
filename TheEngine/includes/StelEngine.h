#pragma once
#include <string>
#include "IInput.h"
#include "ILogger.h"
#include "IGfx.h"
#include "IEvents.h"
#include "IAudio.h"
#include "IWorld.h"

namespace StelEngine
{
	class Engine final
	{
	public :
		bool Init(const std::string& title, int widthScreen, int heightScren);
		void Start();
		const IInput* GetInput() {return m_Input;};
		void ProcessInput();
		void Update(float deltaTime);
		void Render();
		void Shutdown();
		void Exit();
	private:
		bool m_IsInit = false;
		bool m_isRunning = false;
		int m_FPS;
		
		// -----------------------
		//		SERVICES
		// -----------------------
		ILogger* m_Logger;
		IInput* m_Input;
		IEvents* m_Events;
		IGfx* m_Gfx;
		IAudio* m_Audio;


		// -----------------------
		//		TESTES
		// -----------------------
		float m_Speed;
		StelPointF* m_Position;

		//Fonts Loadeds
		size_t m_FontMerlovaz;

		// Musics
		size_t m_AmbianceMusic;
		//Audios
		size_t m_RemoveSfx;

		IWorld* m_World;
	public:
		ILogger* GetLoggerService() { return m_Logger; };
		IInput* GetInputService() { return m_Input; };
		IEvents* GetEventService() { return m_Events; };
		IGfx* GetGfxService() { return m_Gfx; };
		IAudio* GetAudioService() { return m_Audio; };

	};
}