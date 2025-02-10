#include  "gamestate.h"
#include "level.h"
#include  "player.h"
#include  "pipes.h"
#include  "floor.h"
#include  <thread>
#include  <chrono>
#include  "gameobject.h"
#include  "util.h"


void GameState::update(float dt)
{
	if (status == STATUS_START)
	{
		updateStartScreen();
	}
	else if (status == STATUS_PLAYING)
	{
		updateLevelScreen(dt);
		m_pipes->checkcollision();
		m_floor->checkcollision();
	}
	else
	{
		updateOverScreen();
	}
}
void GameState::updateStartScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_SPACE))
	{
		status = STATUS_PLAYING;
	}

	graphics::Brush br2;
	float p = 0.5f + fabs(cos(graphics::getGlobalTime() / 1000.0f));
	br2.fill_color[0] = p; // Red
	br2.fill_color[1] = p; // Green
	br2.fill_color[2] = p; // Blue

	//float p = 0.5f + fabs(cos(graphics::getGlobalTime() / 1000.0f));
	//SETCOLOR(m_state.m_brush_background.fill_color, p, p, p);

}

void GameState::updateLevelScreen(float dt)
{
	if (dt > 500)
		return;

	float  sleep_time = std::max(0.0f, 17.0f - dt);
	std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleep_time));

	if (!m_current_level)
		return;

	m_current_level->update(dt);
	m_debugging = graphics::getKeyState(graphics::SCANCODE_0);
	m_pipes->update(dt);
	m_floor->update(dt);

	if (graphics::getKeyState(graphics::SCANCODE_CAPSLOCK))
	{
		status = STATUS_START;
	}

	if (graphics::getKeyState(graphics::SCANCODE_LSHIFT))
	{
		status = STATUS_OVER;
	}

}

void GameState::updateOverScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_SPACE))
	{
		
		score = 0;
		
		GameState::init();
		status = STATUS_PLAYING;
	}

	if (graphics::getKeyState(graphics::SCANCODE_CAPSLOCK))
	{
		status = STATUS_START;
	}
}

void GameState::drawStartScreen()
{
	graphics::Brush br;
	graphics::Brush br2;
	/*char info[40];
	sprintf_s(info, "Press SPACE to start");
	graphics::drawText(m_canvas_width/2, m_canvas_height/2, 30, info, br2);*/

	float brightness = 0.5f + 0.5f * sin(graphics::getGlobalTime() / 150.0f);
	brightness = std::max(brightness, 0.2f);
	br2.fill_color[0] = brightness;
	br2.fill_color[1] = brightness;
	br2.fill_color[2] = brightness;

	br.outline_opacity = 0.0f;
	br.texture = getFullAssetPath("town.png");
	graphics::drawRect(m_canvas_width / 2, m_canvas_height / 2, 12.0f, 12.0f, br);


	br2.outline_opacity = 0.0f;
	br2.texture = getFullAssetPath("message.png");
	graphics::drawRect(m_canvas_width / 2, m_canvas_height / 2, 3.0f, 3.0f, br2);


}

void GameState::draw()
{
	if (status == STATUS_START)
	{
		drawStartScreen();
	}
	else if (status == STATUS_PLAYING)
	{
		drawLevelScreen();
	}
	else
	{
		drawOverScreen();
	}

}

void GameState::drawLevelScreen()
{
	if (!m_current_level)
		return;

	m_current_level->draw();

	m_pipes->draw();
	m_floor->draw();
}


void GameState::drawOverScreen()
{
	graphics::Brush br;
	graphics::Brush br2;
	br.outline_opacity = 0.0f;
	br.texture = getFullAssetPath("town.png");
	graphics::drawRect(m_canvas_width / 2, m_canvas_height / 2, 12.0f, 12.0f, br);

	br2.outline_opacity = 0.0f;
	br2.texture = getFullAssetPath("gameover.png");
	graphics::drawRect(m_canvas_width / 2, m_canvas_height / 2, 4.0f, 1.0f, br2);

}

GameState::GameState()
{
}

void GameState::init()
{
	m_current_level = new Level();
	m_current_level->init();

	m_player = new Player("Player");
	m_player->init();

	m_pipes = new Pipes();
	m_pipes->init();

	m_floor = new Floor();
	m_floor->init();


	graphics::preloadBitmaps(getAssetDir());

}



GameState* GameState::getInstance()
{
	if (m_unique_instance == nullptr)
		m_unique_instance = new GameState();

	return m_unique_instance;
}

GameState::~GameState()
{
	if (m_player)
		delete m_player;
	if (m_current_level)
		delete m_current_level;
	if (m_pipes)
		delete m_pipes;
	if (m_floor)
		delete m_floor;
}

std::string GameState::getAssetDir()
{
	return m_asset_path;
}

std::string GameState::getFullAssetPath(const std::string& asset)
{
	return  m_asset_path + asset;
}

GameState* GameState::m_unique_instance = nullptr;
