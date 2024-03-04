#include <iostream>
#include <windows.h>
#include <random>
#include <time.h>


// Using <Windows.h> it allows us to use some functions through consts.
// there are more available seen through : https://msdn.microsoft.com/en-us/library/windows/desktop/mt638032(v=vs.85).aspx#example
// BUT i'm a little unsure how to read this ^^^^^ in context :S


// --- GLOBAL CONSTANTS ---
const char* ESC = "x1b";
const char* CSI = "\x1b[";

const char* TITLE = "\x1b[5;20H";
const char* INDENT = "\x1b[5C";
const char* YELLOW = "\x1b[93m";
const char* MAGENTA = "\x1b[95m";
const char* RED = "\x1b[91m";
const char* BLUE = "\x1b[94m";
const char* WHITE = "\x1b[97m";
const char* GREEN = "\x1b[92m";
const char* RESET_COLOR = "\x1b[0m";

const int EMPTY = 0;
const int ENEMY = 1;
const int TREASURE = 2;
const int FOOD = 3;
const int ENTRANCE = 4;
const int EXIT = 5;

const int MAX_RANDOM_TYPE = FOOD+1;

const int MAZE_WIDTH = 10;
const int MAZE_HEIGHT = 6;

const int INDENT_X = 5; // how many spaces to use to indent text. (AKA tab)
const int ROOM_DESC_Y = 8; // line to use for room descriptions
const int MOVEMENT_DESC_Y = 9;
const int MAP_Y = 13; // first line where map is drawn
const int PLAYER_INPUT_X = 30; // character column where player will type their input
const int PLAYER_INPUT_Y = 11; // line where player will type their input

// numbers for numberpad movement instead of WASD.
const int WEST = 4;
const int EAST = 6;
const int NORTH = 8;
const int SOUTH = 2;

// --- FUNCTION PROTOTYPES ---
bool enableVirtualTerminal();
void initialise(int map[MAZE_HEIGHT][MAZE_WIDTH]);
void drawWelcomeMessage();
void drawRoom(int map[MAZE_HEIGHT][MAZE_WIDTH], int x, int y);
void drawMap(int map[MAZE_HEIGHT][MAZE_WIDTH]);
void drawRoomDescription(int roomType);
void drawPlayer(int x, int y);
void drawValidDirection(int x, int y);
int getMovementDirection();


void main()
{
    // create 2D array for map
    int rooms[MAZE_HEIGHT][MAZE_WIDTH];

    bool gameOver = false;
    // player position on map
    int playerX = 0;
    int playerY = 0;

    if (enableVirtualTerminal() == false) 
    {
        std::cout << "The virtual terminal processing mode could be activated." << std::endl;
        std::cout << "Press 'ENTER' to exit." << std::endl;
        std::cin.get();
        return;
    }

    initialise(rooms);

    drawWelcomeMessage();

    // output the map
    drawMap(rooms);

    // --- GAME LOOP ---
    while (!gameOver)
    {
        drawRoomDescription(rooms[playerY][playerX]);
        
        drawPlayer(playerX, playerY);

        if (rooms[playerY][playerX] == EXIT)
        {
            gameOver = true;
            continue;
        }

        // list direction player can take
        drawValidDirection(playerX, playerY);
        int direction = getMovementDirection();

        // before updating the player position, redraw the old room's
        // character over the old player position.
        drawRoom(rooms, playerX, playerY);

        //update player's position using input movement data from user.
        switch (direction) {
        case EAST:
            if (playerX < MAZE_WIDTH - 1) // if less than the far right side of map
                playerX++; // move right one spot
            break;
        case WEST:
            if (playerX > 0) // if more than far left side of map
                playerX--; // move left one spot
            break;
        case NORTH:
            if (playerY > 0) // if lower than top of map (larger Y number means position is lower)
                playerY--; // move them up one spot
            break;
        case SOUTH:
            if (playerY < MAZE_HEIGHT - 1) // if less than height (height number increases going down)
                playerY++; // move down one spot
            break;
        default:
            // direction wasn't valid
            // do nothing... go back to top of loop and ask again (until valid case)
            break;
        }
    } //end of game loop!


    //These lines add's a pause before exiting the console. (waits for a user input)
    //jump to correct location
    std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H"; 
    std::cout << std::endl << INDENT << "Press 'Enter' to exit the program." << std::endl;
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
    
    return;
}



bool enableVirtualTerminal()
{


    /* In WINDOWS we are: Enabling a virtual terminal to control cursor movement, 
    console colour, and other operations when written to output stream.*/

    
    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return false;
    }
    
    DWORD dwMode = 0;
    {
        if (!GetConsoleMode(hOut, &dwMode))
        {
            return false;
        }
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
    {
        return false;
    }
    return true;
}


void initialise(int map[MAZE_HEIGHT][MAZE_WIDTH])
{
    /*
    - Initialise the game, fill the map with rooms
    - this func() takes in a 2d array
    - REMEMBER: anything we do with array[] values persist outside of the func()
        therefore all rooms hold the values we set them to.
    */

    srand(time(nullptr)); // random seed based on system time by setting time() to nullptr.

    //fill arrays with random room type(0-3)
    for (int y = 0; y < MAZE_HEIGHT; y++)
    {
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            int type = rand() % (MAX_RANDOM_TYPE * 2);
            if (type < MAX_RANDOM_TYPE)
                map[y][x] = type;
            else
                map[y][x] = EMPTY;            
        }
    }

    //set the entrance and exit of the maze
    map[0][0] = ENTRANCE;
    map[MAZE_HEIGHT - 1][MAZE_WIDTH - 1] = EXIT;
    
}

void drawWelcomeMessage()
{
    std::cout << TITLE << MAGENTA << "welcome to GAME!" << RESET_COLOR << std::endl;
    std::cout << INDENT << "A game of adventure, danger, and low cunning." << std::endl;
    std::cout << INDENT << "Definitely not related to any other text-based adventure game..." << std::endl;
    
}

void drawRoom(int map[MAZE_HEIGHT][MAZE_WIDTH], int x, int y)
{
    // find the console output position
    int outX = INDENT_X + (6 * x) + 1;
    int outY = MAP_Y + y;

    // jump to correct location
    std::cout << CSI << outY << ";" << outX << "H";
    // draw the room
    switch (map[y][x])
    {
    case EMPTY:
        std::cout << "[ " << GREEN << "\xB0" << RESET_COLOR << " ]";
        break;
    case ENEMY:
        std::cout << "[ " << RED << "\x94" << RESET_COLOR << " ]";
        break;
    case TREASURE:
        std::cout << "[ " << YELLOW << "$" << RESET_COLOR << " ]";
        break;
    case FOOD:
        std::cout << "[ " << WHITE << "\xcf" << RESET_COLOR << " ]";
        break;
    case ENTRANCE:
        std::cout << "[ " << WHITE << "\xE8" << RESET_COLOR << " ]";
        break;
    case EXIT:
        std::cout << "[ " << WHITE << "\xFE" << RESET_COLOR << " ]";
        break;

    }
}


void drawMap(int map[MAZE_HEIGHT][MAZE_WIDTH])
{
    // reset draw colours
    std::cout << RESET_COLOR;
    for (int y = 0; y < MAZE_HEIGHT; y++)
    {
        std::cout << INDENT;
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            drawRoom(map, x, y);
        }
        std::cout << std::endl;
    }
}

void drawRoomDescription(int roomType)
{
 // outputs message depending on type of room player is in.

    // reset draw colours
    std::cout << RESET_COLOR;
    // jump to current location
    std::cout << CSI << ROOM_DESC_Y << ";" << 0 << "H";
    // Delete 4 lines and insert 4 empty lines
    std::cout << CSI << "4M" << CSI << "4L" << std::endl;
    // write description of current room
    switch (roomType)
    {
    case EMPTY:
        std::cout << INDENT << "You are in an empty meadow. There is nothign of note here." << std::endl;
        break;
    case ENEMY:
        std::cout << INDENT << "BEWARE. An enemy is approaching." << std::endl;
        break;
    case TREASURE:
        std::cout << INDENT << "Your efforts have been rewarded. You have found some TREASURE" << std::endl;
        break;
    case FOOD:
        std::cout << INDENT << "At last! You collect some food to sustain you on your journey." << std::endl;
        break;
    case ENTRANCE:
        std::cout << INDENT << "The entrance you use to enter this maze is blocked. There is no going back..." << std::endl;
        break;
    case EXIT:
        std::cout << INDENT << "Despite all odds, you made it to the exit... at last!" << std::endl;
        break;
    }
    
}

void drawPlayer(int x, int y)
{
    // calculate correct pos on the console to draw player, then write player's character to screen
    x = INDENT_X + (6 * x) + 3;
    y = MAP_Y + y;

    // draw player's position on the map
    // move cursor to map pos and dlete character at current position
    std::cout << CSI << MAGENTA << "\x81" << RESET_COLOR;
}

void drawValidDirection(int x, int y)
{
    // determine valiud moves palyerr can make using the player's current position AND dimension of map.
    /*move to correct location on console, then ouitput valid movement directions-
     -according to where player is on the map. NOTE: the use of ternary operators! */ 

    // reset draw colours
    std::cout << RESET_COLOR;
    //jump to correct locatiopn
    std::cout << CSI << MOVEMENT_DESC_Y + 1 << ";" << 0 << "H";
    std::cout << INDENT << "You can see paths leading to the " <<
        ((x > 0) ? "west, " : "") <<
        ((x < MAZE_WIDTH - 1) ? "east, " : "") <<
        ((y > 0) ? "north, " : "") <<
        ((y < MAZE_WIDTH - 1) ? "south, " : "") << std::endl;
}

int getMovementDirection()
{
    // jump to correct location
    std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
    std::cout << INDENT << "Where to now?";

    int direction;
    // move cursor to position for player to enter input
    std::cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H" << YELLOW;

    //clear the input buffer, ready for player input
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());

    std::cin >> direction;
    std::cout << RESET_COLOR;

    if (std::cin.fail())
        return 0;
    return direction;
}