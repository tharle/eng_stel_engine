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
	m_EventsMap = std::map<Uint32, StelEventType>();
	m_EventsMap[SDL_QUIT] = Quit;
	m_EventsMap[SDL_MOUSEBUTTONDOWN] = MouseButtonDown;
	m_EventsMap[SDL_MOUSEBUTTONUP] = MouseButtonUp;
	m_EventsMap[SDL_MOUSEMOTION] = MouseMotion;
	m_EventsMap[SDL_MOUSEWHEEL] = MouseWhell;
}

// TODO: IEvents::StelEvent SdlEvents::Update()
IEvents::StelEvent SdlEvents::PullEvent()
{
	StelEvent stelEvent; // met en private
	stelEvent.type = None;
	SDL_Event _event;
	while (SDL_PollEvent(&_event))
	{
		if (m_EventsMap.find(_event.type) == m_EventsMap.end()) break;

		stelEvent.type = m_EventsMap[_event.type];
		stelEvent.button.position = { _event.button.x, _event.button.y };
		stelEvent.button.id = _event.button.button;
	}

	return stelEvent;
}


