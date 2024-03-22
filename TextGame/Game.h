#pragma once
#include "GameDefines.h"
#include "Room.h"
#include "Player.h"

class Game
{
public:
	Game(); // constructor
	~Game(); // destructor

public:
	bool startup();
	void update();
	void draw();
	bool isGameOver();

private:
	void initializeMap();

	void drawWelcomeMessage();
	void drawMap();
	void drawValidDirections();

	int getCommand();

private:
	bool m_gameOver;
	Room m_map[MAZE_HEIGHT][MAZE_WIDTH];
	Player m_player;
};

