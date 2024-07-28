#pragma once
#include "StelComponent.h"
#include "StelObserver.h"
#include <string>

class StelAtlas;

class Door : public StelComponent, public IUpdatable, public StelObserver<int>
{
private:
	StelAtlas* m_Model = nullptr;
	bool m_IsOpen = false;
	std::string m_NextScene = "";
public:
	Door(StelEntity* parent) : StelComponent(parent) {  }
	virtual ~Door() = default;

	virtual void Start(std::string spriteSheet, std::string nextSceneName);
	virtual void Update(float dt) override;

	virtual void OnNotify(const int& idEvent) override;
};