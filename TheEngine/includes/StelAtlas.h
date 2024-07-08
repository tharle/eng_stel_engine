#pragma once
#include "StelSprite.h"
#include <map>

class StelAtlas: public StelSprite
{
protected:
    std::vector<StelRectI> m_Frames = std::vector<StelRectI>();
public:
    StelAtlas() : StelSprite() {  }
    StelAtlas(StelEntity* parent) : StelSprite(parent) {  }
    virtual ~StelAtlas() = default;

    void AddFrame(StelRectI frame);
    void SetFrame(int index);
};
