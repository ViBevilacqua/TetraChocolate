#pragma once
#include "Tetra_O.h"

void Tetra_O::shapeToNextPosition()
{
	/* positions of blocks
	O O
	 @  <- (0.0)
	O O
*/

	set_tetraPivotX(12.0);
	set_tetraPivotZ(-21.0);

	float posX[] = { -1.0, 1.0, 1.0, -1.0 };
	float posZ[] = { 1.0, 1.0, -1.0, -1.0 };

	for (int i = 0; i < 4; i++) {
		blockPivot[0][i] = posX[i];
		blockPivot[1][i] = posZ[i];
	}
	set_min_z_position(-22);
}

void Tetra_O::shapeReadyToStart()
{
	set_tetraPivotX(0.0);
	set_tetraPivotZ(-17.0);
	set_min_z_position(-18);
	set_blocks();
}

Tetra_O::Tetra_O(Model* choco)
{
	//create square shape
	shapeToNextPosition();

	//chocoList initialization
	place_blocks(choco);
}
