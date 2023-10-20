#pragma once
#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#endif
#include "model.h"
using namespace objloader;

class Block
{
	float x, z;
	Model* choco;
protected:
	int chocoType;
	float r, g, b;
	virtual void set_rgb() = 0;
public:
	Block(Model* choco, float x, float z);
	virtual ~Block() {};
	float get_x() const;
	float get_z() const;
	void set_x(float x);
	void set_z(float z);
	void drawBlock(bool withBoundingBox) const;
	void drawBlock(float y) const;
	void drawGoodBlock(float alpha) const;
	int get_chocoType() const;
};

