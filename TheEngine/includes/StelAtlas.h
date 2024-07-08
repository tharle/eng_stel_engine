#pragma once
#include "StelSprite.h"
#include <map>

class StelAtlas: public StelSprite
{
private:
    std::map<std::string, StelRectI> m_Frames = std::map<std::string, StelRectI>();
public:
    StelAtlas() : StelSprite() {  }
    StelAtlas(StelEntity* parent) : StelSprite(parent) {  }
    virtual ~StelAtlas() = default;

    void AddFrame(const std::string& name, StelRectI frame);
    void SetFrame(const std::string& name);
};
