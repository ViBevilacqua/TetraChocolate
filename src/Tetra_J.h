#pragma once
#include "Tetromino.h"
class Tetra_J final : public Tetromino
{
	void shapeToNextPosition() override;
public:
	void shapeReadyToStart() override;
	Tetra_J(Model*);
	~Tetra_J() {};
};