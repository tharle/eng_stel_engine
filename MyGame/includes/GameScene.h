#pragma once
#include "StelScene.h"

class StelEntity;

class GameScene : public StelScene
{
public:
	virtual ~GameScene() = default;
	virtual void Load() override;
	virtual void OnClose() override;
};