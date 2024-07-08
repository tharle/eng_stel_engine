#include "StelEntity.h"
#include "StelComponent.h"

StelEntity::StelEntity() : StelEntity("") {}

StelEntity::StelEntity(std::string name) : m_Name(name) {}

void StelEntity::Update(float dt)
{
    for (IUpdatable* updtable : m_Updatables)
    {
        updtable->Update(dt);
    }
}

void StelEntity::Draw()
{
    for (IDrawable* drawables : m_Drawables)
    {
        drawables->Draw();
    }
}

void StelEntity::Destroy()
{
    for (auto cmp : m_Components)
    {
        if(cmp.second != nullptr) delete cmp.second;
    }

    m_Drawables.clear();
    m_Updatables.clear();
    m_Components.clear();
}

std::string StelEntity::GetName()
{
    return m_Name;
}
