#pragma once
#include "StelScene.h"

class StelEntity;

class GameScene : public StelScene
{
private:
	StelEntity* m_Player;
public:
	virtual ~GameScene() = default;
	virtual void Load() override;
};