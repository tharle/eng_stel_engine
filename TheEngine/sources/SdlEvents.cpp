#include "SdlEvents.h"

SdlEvents::SdlEvents()
{
	InitEventMap();
}

SdlEvents::~SdlEvents()
{
	m_EventsMap.clear();
}

void SdlEvents::InitEventMap()
{
	m_EventSdlMap = std::map<Uint32, StelEventType>();
	m_EventSdlMap[SDL_QUIT] = Quit;
	m_EventSdlMap[SDL_MOUSEBUTTONDOWN] = MouseButtonDown;
	m_EventSdlMap[SDL_MOUSEBUTTONUP] = MouseButtonUp;
	m_EventSdlMap[SDL_MOUSEMOTION] = MouseMotion;
	m_EventSdlMap[SDL_MOUSEWHEEL] = MouseWhell;
}


void SdlEvents::Update()
{
	SDL_Event _event;
	m_EventsMap.clear();
	int order = 0;
	while (SDL_PollEvent(&_event))
	{
		if (m_EventSdlMap.find(_event.type) == m_EventSdlMap.end()) break;
		
		StelEvent stelEvent; // met en private
		stelEvent.order = order++;
		stelEvent.type = m_EventSdlMap[_event.type];
		stelEvent.button.position = { _event.button.x, _event.button.y };
		stelEvent.button.id = _event.button.button;

		m_EventsMap[stelEvent.type] = stelEvent;
	}
}


