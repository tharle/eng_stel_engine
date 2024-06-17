#include "StelEntity.h"
#include "StelComponent.h"

StelEntity::StelEntity() : StelEntity("") {}

StelEntity::StelEntity(const char* name) : m_Name(name) {}

void StelEntity::Update(float dt)
{
    for (StelComponent* comp : m_Components)
    {
        comp->Update(dt);
    }
}

void StelEntity::Draw()
{
    for (StelComponent* comp : m_Components)
    {
        comp->Draw();
    }
}

const char* StelEntity::GetName()
{
    return m_Name;
}

void StelEntity::AddComponent(StelComponent* comp)
{
    m_Components.emplace_back(comp);
}
