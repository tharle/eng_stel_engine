#pragma once
#include "StelComponent.h"
#include "StelObserver.h"
#include "StelSubject.h"

class StelAtlas;

class Chest : public StelComponent, public IUpdatable, public StelObserver<bool>
{
private:
	StelAtlas* m_Model = nullptr;
	int m_CountHeartsTakes = 0;
	int m_ChestAmount = 0;

public:
	Chest(StelEntity* parent) : StelComponent(parent) {  }
	virtual ~Chest() = default;

	virtual void Start(int chestAmount);
	virtual void Update(float dt) override;
	virtual void OnNotify(const bool& value) override;

	bool IsOpen();

	StelSubject<bool> OnGetPearl;
};