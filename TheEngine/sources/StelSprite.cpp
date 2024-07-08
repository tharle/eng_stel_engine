#include "StelSprite.h"


void StelSprite::Start()
{
	m_TextureId = Gfx().LoadTexture(m_Filename);
}

void StelSprite::Draw()
{
	Gfx().DrawTexture(m_TextureId, m_Frame, m_Position, m_Angle, m_Pivot, m_Flip, m_Color);
}

StelSprite* StelSprite::Init(std::string filename, StelRectI frame, StelRectF position )
{
	m_Filename = filename;
	m_Frame = frame;
	m_Position = position;

	return this;
}

void StelSprite::SetPosition(StelPointF position)
{
	m_Position.x = position.x;
	m_Position.y = position.y;
}
