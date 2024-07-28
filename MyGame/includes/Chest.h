#pragma one
#include "StelComponent.h"

class StelAtlas;

class Chest : public StelComponent, public IUpdatable
{
private:
	StelAtlas* m_Model = nullptr;
	bool m_IsOpen = false;
public:
	Chest(StelEntity* parent) : StelComponent(parent) {  }
	virtual ~Chest() = default;

	virtual void Start() override;
	virtual void Update(float dt) override;
};