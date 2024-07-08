#pragma once
#include "IScene.h"

class StelEntity;

class GameScene : public IScene 
{
private:
	StelEntity* m_Player;
public:
	~GameScene();
	virtual void Load() override;
};