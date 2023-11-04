#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

Color Color1[5];
Color Color2[5];
Color Color3[5];
Color Color4[5];
Color Color5[5];

class ColorDesign
{ 
public:
	ColorDesign()
	{

		Color1[0] = Color(255, 204, 187);
		Color2[0] = Color(110, 181, 192);
		Color3[0] = Color(0, 108, 132);
		Color4[0] = Color(226, 232, 228);
		Color5[0] = Color::Red;

		Color1[1] = Color(0, 207, 250);
		Color2[1] = Color(255, 0, 56);
		Color3[1] = Color(255, 206, 56);
		Color4[1] = Color(2, 5, 9);
		Color5[1] = Color(187, 31, 253);

		Color1[2] = Color(128, 88, 115);
		Color2[2] = Color(71, 63, 102);
		Color3[2] = Color(226, 194, 211);
		Color4[2] = Color(206, 123, 134);
		Color5[2] = Color::Red;

		Color1[3] = Color(172, 190, 190);
		Color2[3] = Color(32, 35, 42);
		Color3[3] = Color(244, 244, 239);
		Color4[3] = Color(160, 29, 38);
		Color5[3] = Color::Red;

		Color1[4] = Color(221, 34, 85);
		Color2[4] = Color(252, 202, 111);
		Color3[4] = Color(100, 10, 100);
		Color4[4] = Color(253, 93, 91);
		Color5[4] = Color::Red;
	
	}


};

