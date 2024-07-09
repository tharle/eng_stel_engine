#pragma once
#include "StelScene.h"

class StelEntity;

class MainMenuScene : public StelScene
{
private:
	StelEntity* m_MainMenuEntity;
public:
	~MainMenuScene();
	virtual void Load() override;
};