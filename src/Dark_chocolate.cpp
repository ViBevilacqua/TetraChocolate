#include "Dark_chocolate.h"
void Dark_chocolate::set_rgb()
{
	//dark chocolate color
	r = 0.2470588235294118;
	g = 0.0588235294117647;
	b = 0.0392156862745098;
}

Dark_chocolate::Dark_chocolate(Model* choco, float x, float z) : Block(choco, x, z)
{
	chocoType = 1;
	set_rgb();
}