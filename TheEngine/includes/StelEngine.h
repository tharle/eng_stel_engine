#pragma once
#include <string>
#include "IInput.h"
#include "ILogger.h"
#include "IGfx.h"
#include "IEvents.h"
#include "IAudio.h"
#include "IWorld.h"
#include "IPhysic.h"

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

		bool Init(const std::string& title, StelPointI screenDimension);
		void Start();
		void Exit();
	private:
		virtual ~Engine() = default;
		void ProcessInput();
		void Update(float deltaTime);
		void Render();
		void Shutdown();
	private:
		bool m_IsInit = false;
		bool m_isRunning = false;
		int m_FPS;
		StelPointI m_ScreenDimension;
		
		// -----------------------
		//		SERVICES
		// -----------------------
		ILogger* m_Logger;
		IInput* m_Input;
		IEvents* m_Events;
		IGfx* m_Gfx;
		IAudio* m_Audio;
		IPhysic* m_Physic;
		

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
		IPhysic& GetPhysic() { return *m_Physic; };

	};
}