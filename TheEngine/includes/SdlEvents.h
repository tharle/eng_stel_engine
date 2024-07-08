#pragma once
#include "IEvents.h"
#include "SDL.h"
#include <map>

class SdlEvents : public IEvents 
{
public:
	SdlEvents();
	virtual ~SdlEvents();
private :
	std::map<Uint32, StelEventType> m_EventSdlMap;
	void InitEventMap();
public:
	virtual void Update() override;
};