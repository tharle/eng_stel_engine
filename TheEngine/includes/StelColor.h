#pragma once

typedef unsigned char uchar;


/// <summary>
/// «Color» est une classe qui sert à regrouper et assigner des couleurs. Il donne aussi la possibilité de prédéfinir des couleurs statiques.
/// </summary>
class StelColor {
public:
	StelColor(uchar red, uchar green, uchar blue, uchar alpha);
	StelColor(uchar _red, uchar _green, uchar _blue);
	static const StelColor& Red;
	static const StelColor& Green;
	static const StelColor& Blue;
	uchar red = 255;
	uchar green = 255;
	uchar blue = 255;
	uchar alpha = 255;

};