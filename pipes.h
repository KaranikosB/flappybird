
#pragma once

#include "gameobject.h"
#include "box.h"
#include "Level.h"
#include "sgg\graphics.h"
#include <list>


class Pipes : public GameObject
{
	
	graphics::Brush pipe_block_brush;
	graphics::Brush pipe_block_brush_debug;
	/*score*/
	graphics::Brush score_br;
	
	int ran_num;
	float pipes_gap = 6.0f;
	
	
	
	/*kinhsh twn pipes*/
	float delta_time;

	int current_pipe = 2;
	
	
	/*width height twn pipes ana zebgari katw panw*/
	const float pipe_block_size_width_height[18][2] = {
		{1.5f, 5.0f},/*0*/
		{1.5f, 5.0f},

		{1.5f, 2.0f},/*2*/
		{1.5f, 8.0f},

		{1.5f, 8.0f},/*4*/
		{1.5f, 2.0f},

		{1.5f, 7.0f},/*6*/
		{1.5f, 3.0f},

		{1.5f, 3.0f},/*8*/
		{1.5f, 7.0f},

		{1.5f, 4.0f},/*10*/
		{1.5f, 7.0f},

		{1.5f, 7.0f},/*12*/
		{1.5f, 4.0f},

		{1.5f, 4.0f},/*14*/
		{1.5f, 6.0f},

		{1.5f, 6.0f},/*16*/
		{1.5f, 4.0f},


	};

	

	/*thesh twn pipes x y gia ta pipes pou briskontai katw kai panw*/

	float  m_pipe_pos_xy_down[10][2] = {
		{8.0f, 8.0f},{14.0f, 8.0f},

	};
	float  m_pipe_pos_xy_up[10][2] = {
		{8.0f, -1.0f},{14.0f, -1.0f},

	};



	void drawBlock(int i);
	
	

	void pipe_block_creation();
	void movePipes(float dt);
	int getRandomFromSet();
	void pipe_del();

	/*score*/
	void score_count();
	void print_score();
	/*int score;*/
	

public:
	



	std::vector<float*> pos_pipes_x;
	std::vector<Box*> pipe_blocks;
	

	void init() override;
	void draw() override;
	void update(float dt) override;

	void checkcollision();
	/*getter gia score*/
	

	
	~Pipes() override;


};