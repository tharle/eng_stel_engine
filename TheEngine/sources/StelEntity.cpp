#include "StelEntity.h"
#include "StelComponent.h"

StelEntity::StelEntity() : StelEntity("") {}

StelEntity::StelEntity(const char* name) : m_Name(name) {}

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
    // TODO do destroy
}

const char* StelEntity::GetName()
{
    return m_Name;
}
