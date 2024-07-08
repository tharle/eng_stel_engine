#pragma once
#include "IScene.h"

class StelEntity;

class GameScene : public IScene 
{
private:
	StelEntity* m_Player;
public:
	virtual ~GameScene() = default;
	virtual void Load() override;
};