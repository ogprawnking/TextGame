#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <random>
#include <time.h>

#include "Game.h"
#include "Enemy.h"
#include "Food.h"
#include "Powerup.h"
//#include "GameObject.h"

Game::Game() : m_gameOver{ false }
{
	// uniform initialise game_over here or in startup()
}

Game::~Game()
{
	delete[] m_powerups;
	delete[] m_enemies;
	delete[] m_food;
}

// Create map, set playerPos
bool Game::startup() // on game startup
{
	//initialise srand to nullptr if anywhere else needs to use it.
	srand(time(nullptr));

	initializeMap(); // create map (includes rooms and types)
	initializeEnemies();
	initializePowerups();
	initializeFood();
		
	m_player.setPosition(Point2D{ 0,0 }); // create player position on map

	return true; // game is running = true
}

// Is player at EXIT,
void Game::update()
{
	Point2D playerPos = m_player.getPosition();
	// Check if player position is the same as EXIT room. If so then 'm_gameOver = true;'
	if (m_map[playerPos.y][playerPos.x].getType() == EXIT) {
		m_gameOver = true;
		return;
	}

	int command = getCommand();

	if (command == QUIT) {
		m_gameOver = true;
		return;
	}

	m_player.executeCommand(command, &m_map[playerPos.y][playerPos.x]);

	for (int i = 0; i < m_enemyCount; i++) {
		if (m_enemies[i].isAlive() == false) {
			Point2D pos = m_enemies[i].getPosition();
			m_map[pos.y][pos.x].removeGameObject(&m_enemies[i]);
		}
	}
}

// Draw functions
void Game::draw()
{
	// draw directions player can move
	// draw current room desc
	// draw  map
	// draw player
	system("cls");
	Point2D playerPos = m_player.getPosition();
	drawWelcomeMessage();
	// list directions player can move
	drawValidDirections();
	// describe current room of playerPos
	m_map[playerPos.y][playerPos.x].drawDescription();
	//redraw map
	drawMap();
	// draw player's inventory
	m_player.drawInventory();
}

// well... is it?
bool Game::isGameOver() {
	return m_gameOver;
}

// create map
// set xy coordinates of each room. Rooms initialised to EMPTY (from the Room constructor)
// entrance/exit rooms set
void Game::initializeMap()
{ 
	// fill arrays with random room types
	// nested loop... for each row(y), fill the columns(x) with randType of room and update position to x,y position of loop
	for (int y = 0; y < MAZE_HEIGHT; y++) {
		for (int x = 0; x < MAZE_WIDTH; x++) {
			m_map[y][x].setPosition(Point2D{ x,y });
		}
	}

	// set entrance and exit of map/maze (1st box & last box)
	m_map[0][0].setType(ENTRANCE);
	m_map[MAZE_HEIGHT - 1][MAZE_WIDTH - 1].setType(EXIT);
}


// randomly set value for number of enemies to create.
// allocate dynamic array of that size and place enemis RANDOMLY on map
void Game::initializeEnemies()
{
	// create dynamic array of enemies
	// (the number of enemies will change every game upto 4)
	m_enemyCount = 1 + rand() % 4;
	m_enemies = new Enemy[m_enemyCount];

	//randomly place enemies in room on the map
	for (int i = 0; i < m_enemyCount; i++)
	{
		// a bit of math ensures enemies wont spawn directly
		// on or next to entrance
		int x = 2 + (rand() % (MAZE_WIDTH - 3));
		int y = 2 + (rand() % (MAZE_HEIGHT - 3));

		m_enemies[i].setPosition(Point2D{ x,y });
		m_map[y][x].addGameObject(&m_enemies[i]);
	}
}


// create 3 kinds of powerups (potion, sword, shield) and place them randomly around map
void Game::initializePowerups()
{
	// create some powerups
	m_powerupCount = 3;
	m_powerups = new Powerup[m_powerupCount];
	// randomly place the food in the map
	for (int i = 0; i < m_powerupCount; i++)
	{
		char name[30] = "";
		int x = rand() % (MAZE_WIDTH - 1);
		int y = rand() % (MAZE_HEIGHT - 1);

		float HP = 1;
		float ATT = 1;
		float DEF = 1;

		switch (i) {
		case 0:
			strcpy(name, "potion of ");
			m_powerups[i].setHealthMultiplier(1.1f);
			break;
		case 1:
			strcpy(name, "sword of ");
			m_powerups[i].setAttackMultiplier(1.1f);
			break;
		case 2:
			strcpy(name, "shield of ");
			m_powerups[i].setDefenceMultiplier(1.1f);
			break;
		}

		strncat(name, itemNames[(rand() % 15)], 30);
		m_powerups[i].setName(name);
		m_map[y][x].addGameObject(&m_powerups[i]); //********************
	}
}


// creates set number of Food objects and place them randomly.
void Game::initializeFood()
{
	// create some food
	m_foodCount = 3;
	m_food = new Food[m_foodCount];
	// randomly place the food in the map
	for (int i = 0; i < m_foodCount; i++)
	{
		int x = rand() % (MAZE_WIDTH - 1);
		int y = rand() % (MAZE_HEIGHT - 1);
		m_map[y][x].addGameObject(&m_food[i]);
	}
}

// A welcome message :)
void Game::drawWelcomeMessage() {
	std::cout << INDENT << INDENT << "Welcome to ZORP!" << std::endl;
	std::cout << INDENT << "ZORP is a game of adventure, danger, and low cunning." << std::endl;
	std::cout << INDENT << "It is definitely not related to any other text-based adventure game." << std::endl << std::endl;
}

// Draw entire map, draw playertile on playerPos
void Game::drawMap()
{
	/*	Redraw's player sprite of current position
		Redraw's room sprite where player used to be
		This is so there isn't a trail of where the player sprite has been */
	Point2D position = m_player.getPosition(); //Position = current player pos.

	std::cout << std::endl;
	std::cout << std::endl;
	for (int y = 0; y < MAZE_HEIGHT; y++) {
		std::cout << INDENT;
		for (int x = 0; x < MAZE_WIDTH; x++) {

			if (position.x == x && position.y == y) {
				m_player.draw(); // draw player sprite
				continue;
			}

			m_map[y][x].draw(); // redraw map sprites
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

// shows which directions are valid movements. If 'position' is 'inbounds' then show 'direction' else show ""
void Game::drawValidDirections() 
{
	Point2D position = m_player.getPosition(); // get player pos on map

	std::cout << INDENT << "You can see paths leading to the " <<
		((position.x > 0) ? "west, " : "") <<
		((position.x < MAZE_WIDTH - 1) ? "east, " : "") <<
		((position.y > 0) ? "north, " : "") <<
		((position.y < MAZE_HEIGHT - 1) ? "south, " : "") << std::endl;
}

// gets user command for movement or action
int Game::getCommand()
{
// limit user input to 50 characters... For now..
	char input[50] = "\0"; // ALWAYS initialise with nullchar

	std::cout << INDENT << "Enter a command:" << INDENT;

	// clear the input buffer, ready for player input
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());

	std::cin >> input; // Get user input


	bool bMove = false; // aka:boolMove.. change to true if input is any movement variety. (North, sout, east, west)... If 'look' or 'fight' bMove doesn't need to be 'true'
	bool bPickup = false;
	while (input)
	{
		if (strcmp(input, "move") == 0) {
			bMove = true;
		}
		else if (bMove == true) {
			if (strcmp(input, "north") == 0)
				return NORTH;
			if (strcmp(input, "south") == 0)
				return SOUTH;
			if (strcmp(input, "east") == 0)
				return EAST;
			if (strcmp(input, "west") == 0)
				return WEST;
		}
		if (strcmp(input, "look") == 0) {
			return LOOK;
		}
		if (strcmp(input, "fight") == 0) {
			return FIGHT;
		}
		if (strcmp(input, "exit") == 0) {
			return QUIT;
		}
		if (strcmp(input, "pick") == 0) {
			bPickup = true;
		}
		else if (bPickup == true){
			if (strcmp(input, "up") == 0)
			return PICKUP;
		}


		char next = std::cin.peek();
		if (next == '\n' || next == EOF)
			break;
		std::cin >> input;
	}

	return 0;
}



