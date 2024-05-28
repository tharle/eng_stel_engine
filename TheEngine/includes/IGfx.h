
#pragma once
class IGfx
{
public:
	virtual void FillRect(int x, int y, int w, int h) = 0;
	virtual void DrawLine(float x1, float y1, float x2, float y2) = 0;
};