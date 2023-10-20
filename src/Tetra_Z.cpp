#include "Tetra_Z.h"

void Tetra_Z::shapeToNextPosition()
{
	/* positions of blocks

		Z	Z

	(0;0)-> Z	Z
*/
	set_tetraPivotX(13.0);
	set_tetraPivotZ(-20.0);

	float posX[] = { -2.0, 0.0, 0.0, 2.0 };
	float posZ[] = { -2.0, -2.0, 0.0, 0.0 };

	for (int i = 0; i < 4; i++) {
		blockPivot[0][i] = posX[i];
		blockPivot[1][i] = posZ[i];
	}
	set_min_z_position(-22);
}

void Tetra_Z::shapeReadyToStart()
{
	set_tetraPivotX(-1.0);
	set_tetraPivotZ(-16.0);
	set_min_z_position(-18);
	set_blocks();
}

Tetra_Z::Tetra_Z(Model* choco)
{
	//create Z shape
	shapeToNextPosition();

	//chocoList initialization
	place_blocks(choco);
}