#pragma once
#include "StelAtlas.h"
#include <map>

class StelAnimation:  public StelAtlas
{
private:
	bool m_IsLoop;
	std::map<const std::string&, std::vector<int>> m_Clips;
public:	
	void InitAnimation(int frameInRows, StelPointI m_Start, StelPointI dimension);
	void AddClip(const std::string& name, int start, int count, float delay);
	void Stop();
	void Play(const std::string& name, bool loop);

};