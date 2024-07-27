#include "StelSprite.h"


void StelSprite::Start()
{
	m_TextureId = Gfx().LoadTexture(m_Filename);
}

void StelSprite::Draw()
{
	Gfx().DrawTexture(m_TextureId, m_Frame, GetTransform().GetTrueRect(), GetTransform().Angle, m_Pivot, m_Flip, m_Color);
}

 StelPointI StelSprite::GetTextureSize() 
{
	 return Gfx().GetTextureSize(m_TextureId);
}

StelSprite* StelSprite::Init(std::string filename)
{
	m_Filename = filename;
	return this;
}
