#pragma once
//#include "StelEngine.h"

class IScene
{
public:
	virtual ~IScene() = default;
	virtual void Load() = 0;
};

