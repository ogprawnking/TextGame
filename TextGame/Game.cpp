#include "Game.h"
#include <iostream>
//#include <random>
//#include <time.h>

Game::Game() : m_gameOver{false}
{
	// uniform initialise game_over here or in startup()
}

Game::~Game()
{
}

// Create map, set playerPos
bool Game::startup() // on game startup
{
	initializeMap(); // create map (includes rooms and types)
		
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

	if (m_player.executeCommand(command, m_map[playerPos.y][playerPos.x].getType())) // execute direction player input i.e. N, S, E, W
		return;

	m_map[playerPos.y][playerPos.x].executeCommand(command);
}

// Draw functions
void Game::draw()
{
	// draw directions player can move
	// draw current room desc
	// draw  map
	// draw player
	Point2D playerPos = m_player.getPosition();
	system("cls");
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
void Game::initializeMap()
{ 
	srand(time(nullptr));

	// fill arrays with random room types
	// nested loop... for each row(y), fill the columns(x) with randType of room and update position to x,y position of loop
	for (int y = 0; y < MAZE_HEIGHT; y++){
		for (int x = 0; x < MAZE_WIDTH; x++){
			int type = rand() % (MAX_RANDOM_TYPE * 2);
			if (type < MAX_RANDOM_TYPE) {
				if (type == TREASURE) // if roomType is TREASURE
					type = rand() % 3 + TREASURE_HP; // add treasure of value between Treasure_hp (=6) and Treasure_Def(=8)
				m_map[y][x].setType(type);
			}
			else
				m_map[y][x].setType(EMPTY);
			m_map[y][x].setPosition(Point2D{ x,y });
		}
	}

	// set entrance and exit of map/maze (1st box & last box)
	m_map[0][0].setType(ENTRANCE);
	m_map[MAZE_HEIGHT - 1][MAZE_WIDTH - 1].setType(EXIT);
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



