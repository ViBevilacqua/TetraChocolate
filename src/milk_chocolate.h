#pragma once
#include "Block.h"

class Milk_chocolate final : public Block
{
	virtual void set_rgb() override;
public:
	Milk_chocolate(Model* choco, float x, float z);
	~Milk_chocolate() {};
};
