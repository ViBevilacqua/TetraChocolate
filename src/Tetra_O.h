#pragma once
#include "Tetromino.h"
class Tetra_O final : public Tetromino
{
	void shapeToNextPosition() override;
public:
	void shapeReadyToStart() override;
	Tetra_O(Model *);
	~Tetra_O() {};
};

