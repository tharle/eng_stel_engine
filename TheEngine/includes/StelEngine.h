#pragma once
#include <string>
#include "IInput.h"
#include "ILogger.h"
#include "IGfx.h"
#include "IEvents.h"
#include "IAudio.h"
#include "IWorld.h"

namespace Stel
{
	class Engine final
	{
	public :
		static Engine& Get()
		{
			static Engine _instance;
			return _instance;
		}

		bool Init(const std::string& title, int widthScreen, int heightScren);
		void Start();
		void Exit();
	private:
		//Engine() = default;
		void ProcessInput();
		void Update(float deltaTime);
		void Render();
		void Shutdown();
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

		//Fonts Loadeds
		size_t m_FontMerlovaz;

		IWorld* m_World;
	public:
		ILogger& GetLoggerService() { return *m_Logger; };
		IInput& GetInputService() { return *m_Input; };
		IEvents& GetEventService() { return *m_Events; };
		IGfx& GetGfxService() { return *m_Gfx; };
		IAudio& GetAudioService() { return *m_Audio; };
		IWorld& GetWorld() { return *m_World; };

	};
}