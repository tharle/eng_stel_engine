#pragma once
#include "StelAtlas.h"

class StelAnimation:  public StelAtlas
{
public:
	//void InitAnimation(int frameInRows, StelPointI frameSize);
	//void AddClip(const std::string& name, int start, int count, float delay);
	//void Stop();
	//void Play(const std::string& name, bool loop);
private:
	bool m_IsLoop;

};