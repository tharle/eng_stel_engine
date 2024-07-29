#pragma once
#include <string>
#include "StelEntity.h"

class IScene
{
public:
	virtual ~IScene() = default;
	virtual void Load() = 0;
	virtual void OnClose() = 0;
	virtual StelEntity* Instantiate(const std::string& name) = 0;
};

