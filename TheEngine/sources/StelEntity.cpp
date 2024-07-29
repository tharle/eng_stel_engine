#include "StelEntity.h"
#include "StelComponent.h"

StelEntity::StelEntity() : StelEntity("") {}

StelEntity::StelEntity(std::string name) : StelEntity(name, StelRectF::Zero()) {}

StelEntity::StelEntity(std::string name, StelRectF rect) : m_Name(name), m_Transform(rect), m_IsActive(true)
{
}

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
    m_IsActive = false;
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

bool StelEntity::IsActive()
{
    return m_IsActive;
}

StelTransform StelEntity::GetTransform()
{
    return m_Transform;
}
