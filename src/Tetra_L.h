#pragma once
#include "Tetromino.h"
class Tetra_L final : public Tetromino
{
	void shapeToNextPosition() override;
public:
	void shapeReadyToStart() override;
	Tetra_L(Model*);
	~Tetra_L() {};
};

