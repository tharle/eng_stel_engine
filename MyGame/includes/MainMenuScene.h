#pragma once
#include "StelEngine.h"
#include "IScene.h"

struct PlayerControls;

class MainMenuScene : public IScene
{
private:
	StelEntity* m_Player;
	PlayerControls* m_PlayerControls;
public:
	virtual void Load() override;
};