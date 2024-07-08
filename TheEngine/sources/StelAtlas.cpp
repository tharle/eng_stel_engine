#include "StelAtlas.h"

void StelAtlas::AddFrame(const std::string& name, StelRectI frame)
{
	m_Frames.emplace(name, frame);
}

void StelAtlas::SetFrame(const std::string& name)
{
	if (m_Frames.count(name) == 0) return;

  	m_Frame = m_Frames.at(name);
}
