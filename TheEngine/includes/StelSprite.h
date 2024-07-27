#pragma once
#include "StelComponent.h"
#include "IGfx.h"
#include "IDrawable.h"
#include <string>

class StelEntity;

class StelSprite : public StelComponent,  public IDrawable
{
public:
	StelSprite() : StelComponent() {  }
	StelSprite(StelEntity* parent) : StelComponent(parent) {  }
    virtual ~StelSprite() = default;
	virtual void Start() override;
	virtual void Draw() override;

	StelSprite* Init(std::string filename);
	StelPointI GetTextureSize();
protected:
	std::string m_Filename = "";
	StelRectI m_Frame{0, 0, 0, 0};
	size_t m_TextureId = 0;
	StelRectF m_Pivot{ 0.0f, 0.0f, 0.0f, 0.0f };
	StelFlip m_Flip{false, false};
	StelColor m_Color = StelColor::WHITE;
};