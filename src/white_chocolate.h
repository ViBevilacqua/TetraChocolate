#pragma once
#include "Block.h"


class White_chocolate final : public Block
{
	virtual void set_rgb() override;
public:
	White_chocolate(Model* choco, float x, float z);
	~White_chocolate() {};
};

