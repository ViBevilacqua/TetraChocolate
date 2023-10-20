#pragma once
#include "Block.h"
class Dark_chocolate final : public Block
{
	virtual void set_rgb() override;
public:
	Dark_chocolate(Model * choco, float x, float z);
	~Dark_chocolate() {};
};

