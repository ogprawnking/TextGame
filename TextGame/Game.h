#pragma once

#include "GameDefines.h"
#include "Room.h"
#include "Player.h"

class Enemy;
class Food;
class Powerup;

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
	void initializeEnemies();
	void initializePowerups();
	void initializeFood();

	void drawWelcomeMessage();
	void drawMap();
	void drawValidDirections();

	int getCommand();

private:
	bool m_gameOver;

	Room m_map[MAZE_HEIGHT][MAZE_WIDTH];

	int m_enemyCount;
	Enemy* m_enemies;

	int m_foodCount; // ^ v variables to manage enemy, food, powerup objects in gameClass
	Food* m_food;

	int m_powerupCount;
	Powerup* m_powerups;


	Player m_player;
};

