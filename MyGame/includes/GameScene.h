#pragma once
#include "StelScene.h"

class StelEntity;

class GameScene : public StelScene
{
private :
	std::string m_Name;
public:
	GameScene(std::string name) : StelScene() { m_Name = name; };
	virtual ~GameScene() = default;
	virtual void Load() override;
	virtual void OnClose() override;
};