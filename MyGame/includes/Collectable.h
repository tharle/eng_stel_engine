#pragma once
#include "StelComponent.h"
#include "StelSubject.h"
//#include <string>

class StelAtlas;

class Collectable : public StelComponent, public IUpdatable {
private:
	StelAtlas* m_Model = nullptr;
public:
	Collectable(StelEntity* parent) : StelComponent(parent) {  }
	virtual ~Collectable() = default;

	virtual void Start() override;
	virtual void Update(float dt) override;

	StelSubject<bool> OnItem;
};