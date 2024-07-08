#pragma once
#include "IScene.h"

struct StelEntity;

class MainMenuScene : public IScene
{
private:
	StelEntity* m_MainMenuEntity;
public:
	~MainMenuScene();
	virtual void Load() override;
};