#include "StelSprite.h"


void StelSprite::Start()
{
	m_TextureId = Gfx().LoadTexture(m_Filename);
}

void StelSprite::Draw()
{
	Gfx().DrawTexture(m_TextureId, m_Frame, m_Position, m_Angle, m_Pivot, m_Flip, m_Color);
}

 StelPointI StelSprite::GetTextureSize() 
{
	 return Gfx().GetTextureSize(m_TextureId);
}

StelSprite* StelSprite::Init(std::string filename, StelPointF m_Size)
{
	m_Filename = filename;
	m_Position.w = m_Size.x;
	m_Position.h = m_Size.y;
	return this;
}

void StelSprite::SetPosition(StelPointF position)
{
	m_Position.x = position.x;
	m_Position.y = position.y;
}
