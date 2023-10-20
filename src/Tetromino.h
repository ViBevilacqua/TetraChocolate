#pragma once
#include "block.h"
#include "milk_chocolate.h"
#include "dark_chocolate.h"
#include "white_chocolate.h"
#include "grid.h"
#include <cmath>

using namespace std;

class Tetromino
{
	float tetraPivotX, tetraPivotZ;
	int min_z_position;
	vector <Block*> chocoList;
	bool wallKick(float xT, const vector <vector<float>>& newPivot, const Grid& board);
protected:
	vector <vector<float>> blockPivot;
	void place_blocks(Model* choco);
	void set_tetraPivotX(float x);
	void set_tetraPivotZ(float z);
	void set_min_z_position(int minz);
	void set_blocks();
	virtual void shapeToNextPosition() = 0;
public:
	Tetromino();
	virtual ~Tetromino() {};
	virtual void shapeReadyToStart() = 0;
	void drawObject(bool withBoundingBox) const;
	void drawAsNext() const;
	bool horizontalTranslation(float xT, const Grid& board);
	int moveDown(const Grid& board);
	bool rotateObject(bool isClockwiseRotation, const Grid& board);
	Block* get_chocoBlock(int ind) const;
};