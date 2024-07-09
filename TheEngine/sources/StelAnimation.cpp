#include "StelAnimation.h"


void StelAnimation::Update(float dt) 
{
	if (m_IsPlaying && m_CurrentClip.size() > 0)
	{
		StelFrameClip stelFrameClip = m_CurrentClip[m_IndexFrameClip];

		if (m_AnimationElapseTime < stelFrameClip.Delay) 
		{
			m_AnimationElapseTime += dt;
			return;
		} 

		m_AnimationElapseTime = 0;
		SetFrame(stelFrameClip.FrameIndex);
		m_IndexFrameClip++;

		if (m_IndexFrameClip < m_CurrentClip.size()) return;

		if (m_IsLoop) m_IndexFrameClip = m_IndexFrameClip % m_CurrentClip.size();
		else Stop();
	}
}

void StelAnimation::AddAnimationFrames(int frameInRows, StelPointI start, StelPointI dimension)
{
	//frameInRows
	int x = start.x;
	int y = start.y;

	StelPointI fullSize = GetTextureSize();

	for (int i = 0; i < frameInRows; i++)
	{

		AddFrame({ x, y, dimension.x, dimension.y });

		x += dimension.x;
		if ((x + dimension.x) > fullSize.x) 
		{
			x = 0;
			y += dimension.y;
		}

		if ((y + dimension.y) > fullSize.y)
		{
			// c'est fini
			break;
		}
	}

	SetFrame(0);

}

void StelAnimation::AddClip(const std::string& name, int start, int count, float delay)
{
	if ((start + count) > m_Frames.size()) return;

	std::vector<StelFrameClip> clips;

	for (int i = start; i < start + count; i++)
	{
		StelFrameClip clip;
		clip.FrameIndex = i;
		clip.Delay = delay;
		clips.push_back(clip);
	}

	m_Clips.emplace(name, clips);
}

void StelAnimation::Play(const std::string& name, bool loop)
{
	if (m_CurrentClipName == name) return;
	if (m_Clips.count(name) <= 0)  return;

	m_CurrentClipName = name;
	m_CurrentClip = m_Clips.at(name);
	m_IsLoop = loop;
	m_IsPlaying = true;
}

void StelAnimation::Stop()
{
	m_IsPlaying = false;
	m_CurrentClipName = "";
}