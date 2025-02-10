#include "floor.h"
#include "gamestate.h"
#include "player.h"

void Floor::init()
{
	/*patwma*/
	floor_blocks.push_back(Box(5.0f, 10.3f, 6.0f, 2.1f));
	/*tabani*/
	floor_blocks.push_back(Box(5.0f, -5.5f, 8.0f, 6.3f));
	floor_block_brush.outline_opacity = 0.0f;

}

void Floor::draw()
{

	for (int i = 0; i < 2; i++)
	{
		Box& boxfloor = floor_blocks[i];
		float x = boxfloor.m_pos_x + m_state->m_global_offset_x;
		float y = boxfloor.m_pos_y + m_state->m_global_offset_y;




		floor_block_brush.texture = m_state->getFullAssetPath("base.png");
		if (i == 0) {
			/*patwma*/
			graphics::drawRect(x, y+0.3f, 6.0f, 3.4f, floor_block_brush);
		}
		else {
			/*tabani*/
			graphics::drawRect(x, y, 6.0f, 7.0f, floor_block_brush);

		}
		
	}

}

void Floor::update(float dt)
{
	checkcollision();
}

/*an brei collision stamataei*/
void Floor::checkcollision()
{
	for (auto& boxfloor : floor_blocks) {
		if (m_state->getPlayer()->intersect(boxfloor)) {	
				m_state->getPlayer()->m_gravity = 0.0f;
				m_state->status = GameState::STATUS_OVER;
		}
	}
	
}
