#include "Milk_chocolate.h"

void Milk_chocolate::set_rgb()
{
	//milk chocolate color
	r = 0.5176470588235294;
	g = 0.3372549019607843;
	b = 0.2352941176470588;
}

Milk_chocolate::Milk_chocolate(Model* choco, float x, float z) : Block(choco, x, z)
{
	chocoType = 2;
	set_rgb();
}