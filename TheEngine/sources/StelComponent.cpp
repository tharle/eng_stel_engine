#include "StelComponent.h"

StelComponent::StelComponent() 
{
    m_EntityParent = nullptr;
}

StelComponent::StelComponent(StelEntity* parent)
{
    m_EntityParent = parent;
}