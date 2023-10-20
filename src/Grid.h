#pragma once
#include "block.h"
#include <vector>
#include "Model.h"
using namespace std;

class Grid final
{
	vector < vector <Block*> > blockMat;
	float leftEdge, rightEdge, bottomEdge;
	tuple<int, int> xzToId(float x, float z) const;
	int addBlock(Block* chocoBlock);
	bool isFullRow(int id) const;
public:
	Grid(float left, float right, float bottom, Model* choco);
	~Grid();
	bool isEmptyPosition(float x, float z) const;
	float get_leftEdge() const;
	float get_rightEdge() const;
	float get_bottomEdge() const;
	int pushBlock(Block* chocoBlock);
	int clearRow(int idRow);
	void drawBlockOnGrid() const;
	void drawBlockOnGrid(const vector <int>& fullRow) const;
};

