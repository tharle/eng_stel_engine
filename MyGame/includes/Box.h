#pragma once
#include "StelComponent.h"

class StelAtlas;
class LevelManager;

class Box : public StelComponent, public IUpdatable {
private:
	StelAtlas* m_Model = nullptr;
	LevelManager* m_CurrentLevel = nullptr;
	StelRectF m_Collider = StelRectF::Zero(); // only for Tilemaps
public:
	Box(StelEntity* parent) : StelComponent(parent) {  }
	virtual ~Box() = default;

	virtual void Start(char* spriteSheet, StelPointI frame, LevelManager* currentLevel);
	virtual void Update(float dt) override;

	//StelSubject<bool> OnItem;
};