#pragma once
#include "IGfx.h"
#include "IUpdatable.h"
#include <map>

class IEvents
{
public:
	enum StelEventType
	{
		None,
		/* Application events */
		Quit, /**< User-requested quit */

		/* Mouse events */
		MouseMotion, /**< Mouse moved */
		MouseButtonDown,         /**< Mouse button pressed */
		MouseButtonUp,          /**< Mouse button released */
		MouseWhell             /**< Mouse wheel motion */
	};

	struct StelMouseButtonEvent
	{
		int id; // Index
		StelPointI position; // position
	};

	struct StelEvent 
	{
		int order;
		StelMouseButtonEvent button;
		StelEventType  type;
	};	
	
	virtual ~IEvents() = default;
	virtual void Update() = 0;
	virtual bool Contanis(StelEventType eventTypeId, StelEvent& eventOut)
	{
		
		// Checking if the map contains a specific key
		auto it = m_EventsMap.find(eventTypeId);
		if (it != m_EventsMap.end()) {
			eventOut = it->second;
			return true;
		}

		eventOut.type = StelEventType::None;
		return false;
	};

	protected:
	std::map<StelEventType, StelEvent> m_EventsMap;

};