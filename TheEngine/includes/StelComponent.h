#pragma once
#include "StelEntity.h"


class StelComponent
{
public:
    virtual ~StelComponent() = default;
    StelComponent();
    StelComponent(StelEntity* parent);

    virtual void Start() {};
    virtual void Update(float dt) {};
    virtual void Draw() {};
    virtual void Destroy() {};
protected:
    StelEntity* m_EntityParent = nullptr;
};