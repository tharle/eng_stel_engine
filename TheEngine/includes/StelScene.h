#pragma once
#include "IScene.h"


class StelScene : public IScene
{
public:
	virtual ~StelScene() = default;
	virtual void Load() = 0;

	virtual StelEntity* Instantiate(const std::string& name) override;
};