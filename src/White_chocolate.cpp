#include "White_chocolate.h"

void White_chocolate::set_rgb()
{
	//white chocolate color
	r = 0.9490196078431373;
	g = 0.9019607843137255;
	b = 0.7686274509803922;
}

White_chocolate::White_chocolate(Model* choco, float x, float z) : Block(choco, x, z)
{
	chocoType = 3;
	set_rgb();
}

