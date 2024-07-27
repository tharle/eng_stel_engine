#pragma once
#include "StelScene.h"

class StelEntity;

class GameScene : public StelScene
{
private:
	StelEntity* m_Player;
	StelEntity* m_Level;
public:
	virtual ~GameScene() = default;
	virtual void Load() override;
};