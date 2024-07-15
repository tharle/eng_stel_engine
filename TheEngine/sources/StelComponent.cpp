#include "StelComponent.h"
#include "StelEngine.h"

StelComponent::StelComponent() : StelComponent(nullptr)
{
}

StelComponent::StelComponent(StelEntity* parent)
{
    m_EntityParent = parent;
}

IInput& StelComponent::Input()
{
    return Stel::Engine::Get().GetInputService();
}

ILogger& StelComponent::Log()
{
    return Stel::Engine::Get().GetLoggerService();
}

IAudio& StelComponent::Audio()
{
    return Stel::Engine::Get().GetAudioService();
}

IGfx& StelComponent::Gfx()
{
    return Stel::Engine::Get().GetGfxService();
}

IEvents& StelComponent::Events()
{
    return Stel::Engine::Get().GetEventService();
}

IWorld& StelComponent::World()
{
    return Stel::Engine::Get().GetWorld();
}
