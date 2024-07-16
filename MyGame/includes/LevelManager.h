#pragma once
#include "StelComponent.h"
#include "StelTileMap.h"

class LevelManager : public StelComponent, public IUpdatable, public IDrawable {
private:
	StelTileMap m_Background;
public:
	LevelManager(StelEntity* parent) : StelComponent(parent) {  }
	virtual ~LevelManager() = default;
	virtual void Start() override;
	virtual void Update(float dt) override;
	virtual void Draw() override;

	bool IsColliding(StelRectF rect);
};