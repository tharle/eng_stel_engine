#pragma once
#include "StelAtlas.h"
#include <map>

struct StelFrameClip
{
	int FrameIndex;
	float Delay;
	bool Playing;
};

class StelAnimation:  public StelAtlas, public IUpdatable
{
private:
	bool m_IsLoop = false;
	bool m_IsPlaying = false;
	float m_AnimationElapseTime = 0.0f;
	int m_IndexFrameClip = 0;
	std::string m_CurrentClipName = "";
	std::vector<StelFrameClip> m_CurrentClip = std::vector<StelFrameClip>();
	std::map<std::string, std::vector<StelFrameClip>> m_Clips = std::map<std::string, std::vector<StelFrameClip>>();

public:	
	StelAnimation() : StelAtlas() {  }
	StelAnimation(StelEntity* parent) : StelAtlas(parent) {  }
	virtual ~StelAnimation() = default;
	virtual void Update(float dt);
	void AddAnimationFrames(int frameInRows, StelPointI m_Start, StelPointI dimension);
	void AddClip(const std::string& name, int start, int count, float delay);
	void Stop();
	void Play(const std::string& name, bool loop);

};