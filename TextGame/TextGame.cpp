#include <iostream>
#include <windows.h>
#include <random>
#include <time.h>


// Using <Windows.h> it allows us to use some functions through consts.
// there are more available seen through : https://msdn.microsoft.com/en-us/library/windows/desktop/mt638032(v=vs.85).aspx#example
// BUT i'm a little unsure how to read this ^^^^^ in context :S

const char* ESC = "x1b";
const char* CSI = "\x1b[";

const char* TITLE = "\x1b[5;20H";
const char* INDENT = "\x1b[5C";
const char* YELLOW = "\x1b[93m";
const char* MAGENTA = "\x1b[95m";
const char* RESET_COLOR = "\x1b[0m";
const char* SAVE_CURSOR_POS = "\x1b[s";
const char* RESTORE_CURSOR_POS = "\x1b[u";


const char* RED = "\x1b[91m";
const char* BLUE = "\x1b[94m";
const char* WHITE = "\x1b[97m";
const char* GREEN = "\x1b[92m";



void main()
{
    const int EMPTY = 0;
    const int ENEMY = 1;
    const int TREASURE = 2;
    const int FOOD = 3;
    const int ENTRANCE = 4;
    const int EXIT = 5;
    const int MAX_RANDOM_TYPE = FOOD+1;

    const int MAZE_WIDTH = 10;
    const int MAZE_HEIGHT = 6;

    const int INDENT_X = 5; // how manyt spaces to use to indent text. (AKA tab)
    const int ROOM_DESC_Y = 8; // line to use for room descriptions
    const int MAP_Y = 13; // first line where map is drawn
    const int PLAYER_INPUT_X = 30; // character column where player will type their input
    const int PLAYER_INPUT_Y = 11; // line where player will type their input

    // numbers for numberpad movement instead of WASD.
    const int WEST = 4;
    const int EAST = 6;
    const int NORTH = 8;
    const int SOUTH = 2;


    /* In WINDOWS, to be able to pass commands to the terminal to control the display of text,
    we need to enable virtual terminal sequences. */
    
    // Set output mode to handle virtual terminal sequences
    DWORD dwMode = 0;
    HANDLE hOut = GetStdHandle (STD_OUTPUT_HANDLE);
    GetConsoleMode (hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    
    
    // Beginning of main code (Variables are first up)
    int height = 0;
    char firstLetterOfName = 0;
    int avatarHP = 0;
    

    //  -----   MAP  ----
    // create 2D array for map
    int rooms[MAZE_HEIGHT][MAZE_WIDTH];

    srand(time(nullptr)); // random seed based on system time by setting tim() to nullptr.
    
    //fill arrays with random room type(0-3)
    for (int y = 0; y < MAZE_HEIGHT; y++)
    {
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            int type = rand() % (MAX_RANDOM_TYPE * 2);
            if (type < MAX_RANDOM_TYPE)
                rooms[y][x] = type;
            else
                rooms[y][x] = EMPTY;            
        }
    }
    //set the entrance and exit of the maze
    rooms[0][0] = ENTRANCE;
    rooms[MAZE_HEIGHT - 1][MAZE_WIDTH - 1] = EXIT;

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << TITLE << MAGENTA << "welcome to GAME!" << RESET_COLOR << std::endl;
    std::cout << INDENT << "A game of adventure, danger, and low cunning." << std::endl;
    std::cout << INDENT << "It's definitely not related to any other text-based adventure game." << std::endl;
    std::cout << "First, some questions..." << std::endl;
    
    // saving cursor position
    std::cout << SAVE_CURSOR_POS;

    // print rooms for maze
    
    std::cout << CSI << MAP_Y << ";" << 0 << "H";
    for (int y = 0; y < MAZE_HEIGHT; y++)
    {
        std::cout << INDENT;
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            switch (rooms[y][x])
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
        std::cout << std::endl;
    }
    
    bool gameOver = false;
    // player position on map
    int playerX = 0;
    int playerY = 0;

    //game loop
    while (!gameOver)
    {
        // prepare screen for output
        // move cursor to start of the 1st Q, then up 1, delete and insert 4 lines
        std::cout << RESTORE_CURSOR_POS << CSI << "A" << CSI << "4M" << CSI << "4L" << std::endl;

        // write description of current room
        switch (rooms[playerY][playerX]) 
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
            std::cout << INDENT << "The entranc you use to enter this maze is blocked. There is no going back." << std::endl;
            break;
        case EXIT:
            std::cout << INDENT << "Despite all odds, you made it to the exit... CONGRATULATIONS!" << std::endl;
            gameOver = true;
            continue;
        } 
        // list directions the player can take
        std::cout << INDENT << "You can see paths leading to the " <<
            ((playerX > 0) ? "west, " : "") <<
            ((playerX < MAZE_WIDTH - 1) ? "east, " : "") <<
            ((playerX > 0) ? "north, " : "") <<
            ((playerX < MAZE_WIDTH - 1) ? "south, " : "") << std::endl;

        std::cout << INDENT << "Where to now?";

        int x = INDENT_X + (5 * playerX) + 3;
        int y = MAP_Y + playerY;
        
        // draw player's position on map
        // move cursor to map pos and delete character at current position
        std::cout << CSI << y << ";" << x << "H";
        std::cout << MAGENTA << "\x81";

        // move cursor to position for player to enter input
        std::cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H" << YELLOW;

        // clear input buffer, ready for player input
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());

        int direction = 0;
        std::cin >> direction;
        std::cout << RESET_COLOR;

        if (std::cin.fail())
            continue;   // go back to top of the game loop and ask again




        // before updating player position, redraw the old room character over-
        // -the old position... Using the current character position.
        std::cout << CSI << y << ";" << x << "H";
        switch (rooms[playerY][playerX])
        {
        case EMPTY:
            std::cout << GREEN << "\xB0" << RESET_COLOR;
            break;
        case ENEMY:
            std::cout << RED << "\x94" << RESET_COLOR;
            break;
        case TREASURE:
            std::cout << YELLOW << "$" << RESET_COLOR;
            break;
        case FOOD:
            std::cout << WHITE << "\xcf" << RESET_COLOR;
            break;
        case ENTRANCE:
            std::cout << WHITE << "\xE8" << RESET_COLOR;
            break;
        case EXIT:
            std::cout << WHITE << "\xFE" << RESET_COLOR;
            break;
        }
        
        // update player's 'X' & 'Y' position Using the input from the user.

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
            // do nothing, go back to top of loop and ask again (until valid case)
            break;
        }
    } //end of game loop! ☻
    
    //These lines add's a pause before exiting the console. (waits for a user input)
    std::cout << std::endl << INDENT << "Press 'Enter' to exit the program." << std::endl;
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
    
    
    return;
}