#pragma once
#include "../Wall.h"

class GiantBlock: 
    public Wall {
	public:
	GiantBlock(Barta::Vector2f initialPosition);
	~GiantBlock() noexcept = default;

	private:
};

