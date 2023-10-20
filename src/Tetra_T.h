#pragma once
#include "Tetromino.h"
class Tetra_T final : public Tetromino
{
	void shapeToNextPosition() override;
public:
	void shapeReadyToStart() override;
	Tetra_T(Model*);
	~Tetra_T() {};
};

