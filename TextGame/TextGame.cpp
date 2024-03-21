#include <iostream>
#include <random>
#include <time.h>



// --- GLOBAL CONSTANTS ---
// Room tile characters
const char* INDENT = "\t";
const char* EMPTY_TILE = "[ \xb0 ]";
const char* ENEMY_TILE = "[ \x94 ]";
const char* TREASURE_TILE = "[ $ ]";
const char* FOOD_TILE = "[ \xcf ]";
const char* ENTRANCE_TILE = "[ \x9d ]";
const char* EXIT_TILE = "[ \xFE ]";
const char* PLAYER_TILE = "[ \x81 ]";
// numbers for room recognition
const int EMPTY = 0;
const int ENEMY = 1;
const int TREASURE = 2;
const int FOOD = 3;
const int ENTRANCE = 4;
const int EXIT = 5;
const int MAX_RANDOM_TYPE = FOOD + 1;

const int MAZE_WIDTH = 10;
const int MAZE_HEIGHT = 6;
// numbers for user input to move (instead of wasd)
const int WEST = 4;
const int EAST = 6;
const int NORTH = 8;
const int SOUTH = 2;
const int LOOK = 9;
const int FIGHT = 10;




// structs
struct Point2D {
	int x;
	int y;
};

// --- FUNCTION PROTOTYPES ---
void initialise(int map[MAZE_HEIGHT][MAZE_WIDTH]);
void drawWelcomeMessage();
void drawMap(int map[MAZE_HEIGHT][MAZE_WIDTH], Point2D position);
void drawRoomDescription(int roomType);
void drawValidDirections(Point2D position);
int getCommand();
void waitForInput();




void main() {

	// create a 2D array
	int rooms[MAZE_HEIGHT][MAZE_WIDTH];

	bool gameOver = false;
	// player position
	Point2D player = { 0, 0 }; // struct made for x,y coords

	initialise(rooms);

	// --- GAME LOOP ---
	while (!gameOver)
	{
		system("cls"); // clear screen

		drawWelcomeMessage();

		// output the map
		drawMap(rooms, player);

		// write description of current room
		drawRoomDescription(rooms[player.y][player.x]);
		if (rooms[player.y][player.x] == EXIT)
		{
			gameOver = true;
			break;
		}

		// list the directions the player can take
		drawValidDirections(player);
		std::cout << INDENT << "Where to now?" << INDENT;

		int command = getCommand();

		// update player's position using input data from user.
		switch (command) {
		case EAST:
			if (player.x < MAZE_WIDTH - 1) // if less than the far right side of map
				player.x++; // move right one spot
			break;
		case WEST:
			if (player.x > 0) // if more than far left side of map
				player.x--; // move left one spot
			break;
		case NORTH:
			if (player.y > 0) // if lower than top of map (larger Y number means position is lower)
				player.y--; // move them up one spot
			break;
		case SOUTH:
			if (player.y < MAZE_HEIGHT - 1) // if less than height (height number increases going down)
				player.y++; // move down one spot
		default:
			// direction wasn't valid
			// do nothing, go back to the top of the loop and ask again
			break;
		case LOOK:
			std::cout << INDENT << "You look around, but see nothing worth mentioning" << std::endl;
			std::cout << "Press 'Enter' to continue.";
			waitForInput(); //clear input buffer and wait for user to press 'any key'
		}

	} // <<< end of the game loop


	// Add's pause before exiting the console. (waits for a user input)
	std::cout << std::endl << INDENT << "Press 'Enter' to exit the program." << std::endl;
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
}



void initialise(int map[MAZE_HEIGHT][MAZE_WIDTH])
{
	srand(time(nullptr));

	// fill the arrays with random room types
	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		for (int x = 0; x < MAZE_WIDTH; x++) {
			int type = rand() % (MAX_RANDOM_TYPE * 2);
			if (type < MAX_RANDOM_TYPE)
				map[y][x] = type;
			else
				map[y][x] = EMPTY;
		}
	}

	// set the entrance and exit of the maze
	map[0][0] = ENTRANCE;
	map[MAZE_HEIGHT - 1][MAZE_WIDTH - 1] = EXIT;
}

void drawWelcomeMessage()
{
	std::cout << INDENT << INDENT << "Welcome to ZORP!" << std::endl;
	std::cout << INDENT << "ZORP is a game of adventure, danger, and low cunning." << std::endl;
	std::cout << INDENT << "It is definitely not related to any other text-based adventure game." << std::endl << std::endl;
}

void drawMap(int map[MAZE_HEIGHT][MAZE_WIDTH], Point2D position)
{
	std::cout << std::endl;
	std::cout << std::endl;
	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		std::cout << INDENT;
		for (int x = 0; x < MAZE_WIDTH; x++) {

			if (position.x == x && position.y == y) {
				// draw the player's position on the map
				std::cout << PLAYER_TILE;
				continue;
			}

			switch (map[y][x])
			{
			case EMPTY:
				std::cout << EMPTY_TILE;
				break;
			case ENEMY:
				std::cout << ENEMY_TILE;
				break;
			case TREASURE:
				std::cout << TREASURE_TILE;
				break;
			case FOOD:
				std::cout << FOOD_TILE;
				break;
			case ENTRANCE:
				std::cout << ENTRANCE_TILE;
				break;
			case EXIT:
				std::cout << EXIT_TILE;
				break;
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void drawRoomDescription(int roomType)
{
	switch (roomType) {
	case EMPTY:
		std::cout << INDENT << "You are in an empty meadow. There is nothing of note here." << std::endl;
		break;
	case ENEMY:
		std::cout << INDENT << "BEWARE. An enemy is approaching." << std::endl;
		break;
	case TREASURE:
		std::cout << INDENT << "Your journey has been rewarded. You have found some treasure" << std::endl;
		break;
	case FOOD:
		std::cout << INDENT << "At last! You collect some food to sustain you on your journey." << std::endl;
		break;
	case ENTRANCE:
		std::cout << INDENT << "The entrance you used to enter this maze is blocked. There is no going back." << std::endl;
		break;
	case EXIT:
		std::cout << INDENT << "Despite all odds, you made it to the exit. Congratulations." << std::endl;
		break;
	}
}

void drawValidDirections(Point2D position)
{
	std::cout << INDENT << "You can see paths leading to the " <<
		((position.x > 0) ? "west, " : "") <<
		((position.x < MAZE_WIDTH - 1) ? "east, " : "") <<
		((position.y > 0) ? "north, " : "") <<
		((position.y < MAZE_HEIGHT - 1) ? "south, " : "") << std::endl;
}

int getCommand()
{
	// limit user input to 50 characters... For now..
	char input[50] = "\0"; // ALWAYS initialise with nullchar
	std::cout << INDENT << "Enter a command:" << INDENT;

	// clear the input buffer, ready for player input
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());

	std::cin >> input; // Get user input


	bool bMove = false; // aka:boolMove.. change to true if input is any movement variety. (North, sout, east, west)... If 'look' or 'fight' bMove doesn't need to be 'true'
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

		char next = std::cin.peek();
		if (next == '\n' || next == EOF)
			break;
		std::cin >> input;
	}
	return 0;

}

void waitForInput() {
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
}