#include "gamestate.h"
#include "pipes.h"
#include "player.h"
#include "util.h"
#include <iostream>
#include <vector>
#include "sgg\graphics.h"
#include <thread>
#include <chrono>


/*ftiaxnoume ta koutia(topothesia onoma png)*/
void Pipes::init()
{
	/*ftiaxnei ta 2 prwta set pipes*/
	pipe_blocks.push_back(new Box(m_pipe_pos_xy_down[0][0], m_pipe_pos_xy_down[0][1],
		pipe_block_size_width_height[0][0]-0.8f,pipe_block_size_width_height[0][1] - 0.8f));
	
	pipe_blocks.push_back(new Box(m_pipe_pos_xy_up[0][0], m_pipe_pos_xy_up[0][1],
		pipe_block_size_width_height[1][0]-0.8f, pipe_block_size_width_height[1][1] - 0.8f));
	
	pipe_blocks.push_back(new Box(m_pipe_pos_xy_down[1][0], m_pipe_pos_xy_down[1][1],
		pipe_block_size_width_height[2][0] - 0.8f, pipe_block_size_width_height[2][1] - 0.8f));
	
	pipe_blocks.push_back(new Box(m_pipe_pos_xy_up[1][0], m_pipe_pos_xy_up[1][1], 
		pipe_block_size_width_height[3][0] - 0.8f, pipe_block_size_width_height[3][1] - 0.8f));
	
	pipe_block_brush.outline_opacity = 0.0f;
	pipe_block_brush_debug.fill_opacity = 0.1f;
	SETCOLOR(pipe_block_brush_debug.fill_color, 0.2f, 1.0f, 0.1f);
	SETCOLOR(pipe_block_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);
	/*grammatoseira*/
	graphics::setFont(m_state->getFullAssetPath("font.ttf"));
}

/*zwgrafizoume ta koutia gia kathe pipe pou kanoume eisagwgh)*/
void Pipes::drawBlock(int i)
{
	/*katw pipe*/ 
	Box& box = *pipe_blocks[i];
	float x = box.m_pos_x + m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;
	float widthbdown = box.m_width;
	float heightbdown = box.m_height;
	pos_pipes_x.push_back(& box.m_pos_x);
	pipe_block_brush.texture = m_state->getFullAssetPath("pipe-green.png");

	/*panw pipe*/
	Box& box2 = *pipe_blocks[i+1];
	float xup = box2.m_pos_x + m_state->m_global_offset_x;
	float yup = box2.m_pos_y + m_state->m_global_offset_y;
	float widthbup = box2.m_width ;
	float heightbup = box2.m_height ;
	pos_pipes_x.push_back(&box2.m_pos_x);
	
	graphics::drawRect(x, y, widthbdown+0.8f, heightbdown + 0.8f, pipe_block_brush);
	
	pipe_block_brush.texture = m_state->getFullAssetPath("pipe-green2.png");

	graphics::drawRect(xup, yup, widthbup + 0.8f, heightbup + 0.8f, pipe_block_brush);

}





void Pipes::pipe_block_creation()
{
	ran_num = getRandomFromSet();
	

	if (pipe_blocks.size() == 0 || pipe_blocks.size() == 2 || pipe_blocks.size() == 4 || pipe_blocks.size() == 6 ){
		ran_num = getRandomFromSet();
		

		pipe_blocks.push_back(new Box(m_pipe_pos_xy_down[1][0] + pipes_gap, m_pipe_pos_xy_down[1][1],
			pipe_block_size_width_height[ran_num][0] - 0.8f, pipe_block_size_width_height[ran_num][1] - 0.8f));

		pipe_blocks.push_back(new Box(m_pipe_pos_xy_up[1][0] + pipes_gap, m_pipe_pos_xy_up[1][1],
			pipe_block_size_width_height[ran_num + 1][0] - 0.8f, pipe_block_size_width_height[ran_num + 1][1] - 0.8f));
		
		
		
		
		if (current_pipe<4) {
			pipes_gap += pipes_gap;
		}
		else {
			pipes_gap = 0.0f;

		}
		if (current_pipe < 4) {
			current_pipe += 1;
		}else {
			current_pipe = 0;
		}
	}	
}


/*ta pipes kinountai pros ton paikth*/
void Pipes::movePipes(float dt)
{
		delta_time = dt / 5000.0f;
		
		int sizeofx = pos_pipes_x.size();
	
			
			for (int p = 0; p < sizeofx; p++)
			{
				if (*pos_pipes_x[p])
					*pos_pipes_x[p] -= 0.01 * delta_time;
			}
					
}

/*briskei an akoumphsame ta pipes*/
void Pipes::checkcollision()
{
	for (auto& box : pipe_blocks) {
		if (m_state->getPlayer()->intersect(*box)) {
			m_state->status = GameState::STATUS_OVER;
			
		}	
	}
}



int Pipes::getRandomFromSet()
{
	
	std::vector<int> numbers = { 0, 2, 4, 6, 8, 10, 12, 14, 16 };

	// Seed 
	float x = graphics::getGlobalTime();
	srand(x);

	// deikths 
	int randominteger = std::rand() % numbers.size();
	    
	// Return the number at the randomly selected index
	int randomNumber = numbers[randominteger];
	
	return randomNumber;
}

/*diagrafh pipes*/
void Pipes::pipe_del()
{	
	for (auto pipe_to_del = pipe_blocks.begin(); pipe_to_del != pipe_blocks.end();){
		float x = (*pipe_to_del)->m_pos_x ;
		
		
		
		if (x < 1.0f) {
			
			delete* pipe_to_del;
			pipe_to_del = pipe_blocks.erase(pipe_to_del); // Remove the pointer from the vector and update the iterator	
		
			delete* pipe_to_del;
			pipe_to_del = pipe_blocks.erase(pipe_to_del);

			
		
		}
		else {
			++pipe_to_del; // Only increment the iterator if no element was erased
			++pipe_to_del;
		}
	}
}

/*kaloume thn funcion pou zwgrafizei ta pipes*/
void Pipes::draw()
{
	for (auto pipe_to_draw = pipe_blocks.begin(); pipe_to_draw != pipe_blocks.end();)
	{
		
		size_t index = std::distance(pipe_blocks.begin(), pipe_to_draw);
		Pipes::drawBlock(index);

		++pipe_to_draw;
		++pipe_to_draw;
	}
	print_score();
}

void Pipes::update(float dt)
{
	pipe_block_creation();
	movePipes(dt);
	checkcollision();
	score_count();
	
	/*if (collis == false) { pipe_block_creation(); }*/
	
	
	pipe_del();
}




/*metraei to score*/
void Pipes::score_count()
{
	for (auto pipe_to_score = pipe_blocks.begin(); pipe_to_score != pipe_blocks.end();)
	{
		float x = (*pipe_to_score)->m_pos_x;
		if (x < 5.0f && x > 4.98f) {
			m_state->score++;
		}
		++pipe_to_score;
	}
}


/*kanei print to score panw aristera*/
void Pipes::print_score()
{
	float x = m_state->getCanvasWidth()/2-2.9f;
	float y = m_state->getCanvasHeight()/2-2.5f;
	std::string s = std::to_string(m_state->score);
	
	graphics::drawText(x, y, 0.3, s, score_br);

}

Pipes::~Pipes() {
	for (auto box : pipe_blocks) {
		delete box;
	}
	for (auto box2 : pipe_blocks) {
		delete box2;
	}
	pipe_blocks.clear();
}
