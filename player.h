#pragma once

#include "gameobject.h"
#include "box.h"
#include "sgg\graphics.h"

class Player : public GameObject, public Box
{
	graphics::Brush m_brush_player;
	

	float m_accel_vertical1 = 0.0f;

	void movePlayer(float dt);

	

public:

	

	float m_vy = 0.0f;


	Player(std::string name) : GameObject(name) {}
	float m_gravity = 10.0f;
	void update(float dt) override;
	void init() override;
	void draw() override; 

};