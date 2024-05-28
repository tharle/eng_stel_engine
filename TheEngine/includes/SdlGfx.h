#pragma once
#include "IGfx.h"

class SdlGfx : public IGfx
{
public:
	virtual void FillRect(int x, int y, int w, int h) override;
	virtual void DrawLine(float x1, float y1, float x2, float y2) override;
};

