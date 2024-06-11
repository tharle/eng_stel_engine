#include "StelColor.h"

const StelColor& StelColor::Red = StelColor(255, 0, 0, 1);
const StelColor& StelColor::Green = StelColor(0, 255, 0, 1);
const StelColor& StelColor::Blue = StelColor(0, 0, 255, 1);

StelColor::StelColor(uchar _red, uchar _green, uchar _blue, uchar _alpha) : 
	red(_red),
	green(_green),
	blue(_blue),
	alpha(_alpha)
{
}

StelColor::StelColor(uchar _red, uchar _green, uchar _blue) : StelColor(_red, _green, _blue, 255)
{
}
