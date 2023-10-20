#pragma once
#include "Tetromino.h"
class Tetra_Z final : public Tetromino
{
	void shapeToNextPosition() override;
public:
	void shapeReadyToStart() override;
	Tetra_Z(Model*);
	~Tetra_Z() {};
};


