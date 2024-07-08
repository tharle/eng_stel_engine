#include "StelAtlas.h"

void StelAtlas::AddFrame(StelRectI frame)
{
	m_Frames.push_back(frame);
}

void StelAtlas::SetFrame(int index)
{
	if (m_Frames.size() <= index) return;

	m_Frame = m_Frames[index];
}
