#pragma once
#include "StelScene.h"

class StelEntity;

class GameScene : public StelScene
{
private:
	StelEntity* m_Player;
	StelEntity* m_Level;
	// Item colletable
	StelEntity* m_Heart1;
	StelEntity* m_Heart2;
	StelEntity* m_Chest;
	StelEntity* m_Door;
public:
	virtual ~GameScene() = default;
	virtual void Load() override;
};