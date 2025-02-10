#pragma once

#include "gameobject.h"
#include "box.h"
#include "Level.h"
#include "sgg\graphics.h"
#include <list>


class Floor : public GameObject
{
	std::vector<Box> floor_blocks;
	graphics::Brush floor_block_brush;

public:
	
	void init() override;
	void draw() override;
	void update(float dt) override;
	
	void checkcollision();
};