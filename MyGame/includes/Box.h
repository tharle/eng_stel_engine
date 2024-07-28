#pragma once
#include "StelComponent.h"

#define OFFSET_SHIFT 10.0f
#define OFFSET_COLLIDER 4.0f

class StelAtlas;
class LevelManager;

class Box : public StelComponent, public IUpdatable {
private:
	StelAtlas* m_Model = nullptr;
	LevelManager* m_CurrentLevel = nullptr;
	StelRectF m_Collider = StelRectF::Zero(); // only for Tilemaps

	void Move(float dt);
public:
	Box(StelEntity* parent) : StelComponent(parent) {  }
	virtual ~Box() = default;

	virtual void Start(char* spriteSheet, StelPointI frame, LevelManager* currentLevel);
	virtual void Update(float dt) override;

	//StelSubject<bool> OnItem;
};