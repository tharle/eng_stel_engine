#pragma once
#include "IEvents.h"
#include "SDL.h" // Pas réussi le foward declaration
#include <map>

//class Uint32;

class SdlEvents : public IEvents 
{
public:
	SdlEvents();
	virtual ~SdlEvents();
private :
	std::map<Uint32, StelEventType> m_EventSdlMap = std::map<Uint32, StelEventType>();
	void InitEventMap();
public:
	virtual void Update() override;
};