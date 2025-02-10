#include "player.h"
#include "sgg\graphics.h"
#include "gamestate.h"


/*jump */
void Player::movePlayer(float dt)
{
	float delta_time = dt / 1000.0f;


	if (graphics::getKeyState(graphics::SCANCODE_SPACE) >= m_gravity / 10.0f)
	{
		m_accel_vertical1 = 0.0f;
		m_vy = -m_gravity / 3.5f;
	}
	else
	{
		m_accel_vertical1 += delta_time * m_gravity;
	}

	if (m_accel_vertical1 >= m_gravity)
	{
		m_accel_vertical1 = m_gravity;

	}

	m_vy += delta_time * m_accel_vertical1;
	m_pos_y += m_vy * delta_time;
}


void Player::update(float dt)
{



	movePlayer(dt);


	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;
}

void Player::init()
{
	m_pos_x = 5.0f;
	m_pos_y = 5.0f;

	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

	m_brush_player.fill_opacity = 1.0f;
	m_brush_player.outline_opacity = 0.0f;
	m_brush_player.texture = m_state->getFullAssetPath("mario.png");

}

void Player::draw()
{
	graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, 0.3f , 0.3f, m_brush_player);
}

