#pragma once
#include "StelComponent.h"
#include "StelTileMap.h"

class GameManager : public StelComponent, public IUpdatable, public IDrawable {
private:
	StelTileMap m_Background;
public:
	GameManager(StelEntity* parent) : StelComponent(parent) {  }
	virtual ~GameManager() = default;
	virtual void Start() override;
	virtual void Update(float dt) override;
	virtual void Draw() override;
};