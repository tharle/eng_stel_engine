#pragma once
#include "StelEntity.h"
#include "IInput.h"
#include "ILogger.h"
#include "IAudio.h"
#include "IGfx.h"
#include "IEvents.h"


class StelComponent
{
public:
    virtual ~StelComponent() = default;
    StelComponent();
    StelComponent(StelEntity* parent);

    virtual void Start() {};
    virtual void Destroy() {};


    // ----------------------------------------
    //  Services dispo pour les composents
    // ----------------------------------------
    IInput& Input();
    ILogger& Log();
    IAudio& Audio();
    IGfx& Gfx();
    IEvents& Events();
protected:
    StelEntity* m_EntityParent = nullptr;
};