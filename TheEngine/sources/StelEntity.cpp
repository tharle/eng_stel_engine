#include "StelEntity.h"
#include "StelComponent.h"

StelEntity::StelEntity() : StelEntity("") {}

StelEntity::StelEntity(const char* name) : m_Name(name) {}

void StelEntity::Update(float dt)
{
    for (IUpdable* updtable : m_Updatables)
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

const char* StelEntity::GetName()
{
    return m_Name;
}

template<typename T>
/* inline*/ void StelEntity::AddComponent(T* comp)
{
    T temp;
    const type_info* type = &typeid(*temp); // _comp
    m_Components.emplace(type, comp); // cmp

    IUpdable updable =  dynamic_cast<IUpdable>(comp);
    if (updable != nullptr) m_Updatables(updable);

    IDrawable drawable = dynamic_cast<IDrawable>(comp);
    if (drawable != nullptr) m_Drawables(drawable);
}

template<typename T>
T* StelEntity::GetComponent()
{
    T temp;
    const type_info* type = &typeid(*temp); // _comp
    return m_Components.at(type_info);
}
