#pragma once
#include "Tetromino.h"
class Tetra_S final : public Tetromino
{
	void shapeToNextPosition() override;
public:
	void shapeReadyToStart() override;
	Tetra_S(Model*);
	~Tetra_S() {};
};

