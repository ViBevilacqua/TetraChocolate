#pragma once
#include "Tetromino.h"
class Tetra_I final : public Tetromino
{
	void shapeToNextPosition() override;
public:
	void shapeReadyToStart() override;
	Tetra_I(Model*);
	~Tetra_I() {};
};

