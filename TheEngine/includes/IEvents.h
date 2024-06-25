#pragma once
#include "IGfx.h"

class IEvents
{
public:
	static enum StelEventType
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
		// TODO: int order;
		StelMouseButtonEvent button;
		StelEventType  type;
	};
	
	virtual StelEvent PullEvent() = 0;
};