#pragma once
#include "StelScene.h"

class StelEntity;

class GameSceneLevel1 : public StelScene
{
private :
	std::string m_Name;
public:
	GameSceneLevel1(std::string name) : StelScene() { m_Name = name; };
	virtual ~GameSceneLevel1() = default;
	virtual void Load() override;
	virtual void OnClose() override;
};