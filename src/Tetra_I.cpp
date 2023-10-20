#include "Tetra_I.h"

void Tetra_I::shapeToNextPosition()
{
	/* positions of blocks

 -Z |	I	I	I	I
	+         @
	|         ^
 +Z	|         |
	v       (0;0)
*/
	set_tetraPivotX(14.0);
	set_tetraPivotZ(-19.0);

	float posX[] = { -3.0, -1.0, 1.0, 3.0 };
	float posZ[] = { -1.0, -1.0, -1.0, -1.0 };

	for (int i = 0; i < 4; i++) {
		blockPivot[0][i] = posX[i];
		blockPivot[1][i] = posZ[i];
	}
	set_min_z_position(-20);

}

void Tetra_I::shapeReadyToStart()
{
	set_tetraPivotX(0.0);
	set_tetraPivotZ(-15.0);
	set_min_z_position(-16);
	set_blocks();
}

Tetra_I::Tetra_I(Model* choco)
{
	//create S shape
	shapeToNextPosition();

	//chocoList initialization
	place_blocks(choco);
}