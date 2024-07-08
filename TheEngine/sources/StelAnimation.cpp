#include "StelAnimation.h"

void StelAnimation::InitAnimation(int frameInRows, StelPointI start, StelPointI dimension)
{
	//frameInRows
	int x = start.x;
	int y = start.y;

	StelPointI fullSize = GetTextureSize();

	for (int i = 0; i < frameInRows; i++)
	{

		x += dimension.x;
		if ((x + dimension.x) > fullSize.x) 
		{
			x = 0;
			y += dimension.y;
		}

		if ((y + dimension.y) > fullSize.y)
		{
			// c'est fini
			return;
		}

		AddFrame({ x, y, dimension.x, dimension.y });
	}

}
