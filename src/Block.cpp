#include "Block.h"

Block::Block(Model* choco, float x, float z)
{
	this->choco = choco;
	this->x = x;
	this->z = z;
}

float Block::get_x() const {
	return x;
}

float Block::get_z() const {
	return z;
}

void Block::set_x(float x) {
	this->x = x;
}

void Block::set_z(float z) {
	this->z = z;
}

void Block::drawBlock(bool withBoundingBox) const {
	glPushMatrix();
	glTranslatef(x, 0.75, z);
	glColor4f(r, g, b, 1.0);
	choco->render(withBoundingBox);
	glPopMatrix();
}
void Block::drawBlock(float y) const {
	glPushMatrix();
	glTranslatef(x, y, z);
	glColor4f(r, g, b, 1.0);
	choco->render(false);
	glPopMatrix();
}
void Block::drawGoodBlock(float alpha) const {
	glPushMatrix();
	glTranslatef(x, 0.75, z);
	glColor4f(r, g, b, alpha);
	choco->render(false);
	glPopMatrix();
}

int Block::get_chocoType() const
{
	return chocoType;
}
