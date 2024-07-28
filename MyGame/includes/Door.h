#pragma one
#include "StelComponent.h"

class StelAtlas;

class Door : public StelComponent, public IUpdatable
{
private:
	StelAtlas* m_Model = nullptr;
	bool m_IsOpen = false;
public:
	Door(StelEntity* parent) : StelComponent(parent) {  }
	virtual ~Door() = default;

	virtual void Start() override;
	virtual void Update(float dt) override;
};