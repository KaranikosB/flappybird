#pragma once
#include <string>
#include "sgg\graphics.h"
#include "floor.h"
#include "player.h"
#include "pipes.h"
#include "level.h"

class GameState {
	
	

	void updateStartScreen();
	void updateLevelScreen(float dt);
	void drawStartScreen();
	void drawLevelScreen();
	void updateOverScreen();
	void drawOverScreen();
	std::string m_asset_path = "assets\\";
	float m_canvas_width = 6.0f;
	float m_canvas_height = 6.0f;

	static GameState* m_unique_instance;

	GameState();

	class Player* m_player = 0;
	class Level* m_current_level = 0;
	class Pipes* m_pipes = 0;
	class Floor* m_floor = 0;
	class GameObject* m_state = 0;
	
	/*GameObject* floor1 = new Floor();*/
	/*GameObject* level1 = new Level();*/
	/*GameObject* player1 = new Player("bird");*/
	/*GameObject* pipes1 = new Pipes();*/
public:

	
	typedef enum { STATUS_START, STATUS_PLAYING, STATUS_OVER } status_t;
	status_t status = STATUS_START;

	float m_global_offset_x = 0.0f;
	float m_global_offset_y = 0.0f;

	bool m_debugging = false;

	void init();
	void draw();
	void update(float dt);

	int score=0;

	static GameState* getInstance();
	~GameState();

	float getCanvasWidth() { return m_canvas_width; }
	float getCanvasHeight() { return m_canvas_height; }

	std::string getAssetDir();
	std::string getFullAssetPath(const std::string& asset);

	class Player* getPlayer() { return m_player; }

};