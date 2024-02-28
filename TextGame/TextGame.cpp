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
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    for (int y = 0; y < MAZE_HEIGHT; y++)
    {
        std::cout << INDENT;
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            switch (rooms[y][x])
            {
            case EMPTY:
                std::cout << "[ " << GREEN << "\xDB" << RESET_COLOR << " ]";
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
                std::cout << "[" << WHITE << "EN" << RESET_COLOR << " ]";
                break;
            case EXIT:
                std::cout << "[ " << WHITE << "EX" << RESET_COLOR << "]";
                break;

            }
            
        }
        std::cout << std::endl;
    }

    // move the cursor back to the top of the map
    std::cout << RESTORE_CURSOR_POS;
    std::cout << INDENT << "How tall are you, in centimeters? " << INDENT << YELLOW;

    std::cin >> height;
    std::cout << RESET_COLOR << std::endl;

    if (std::cin.fail()) { 
    //fail() func = true if wrong data type entered into input.
        std::cout << INDENT << "You have failed the first challenge and are eaten by a grue.";
    }
    else {
        std::cout << INDENT << "You entered " << height;
    }


    //clears any data inside the input buffer
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail()); /*needs argument that tells how many characters to ignore.
    Therefore cin.rdbuf()->in_avail() reads how many characters remain in buffer and pass valuye to cin.ignore().*/
    std::cin.get(); // Typically used for enter key, so that the game doesn't go through too fast. (Needs no input inside buffer)
    //move the cursor to the start of the 1st question
    std::cout << RESTORE_CURSOR_POS;
    // THEN delete the next 3 lines of text
    std::cout << CSI << "3M";
    // insert 3 lines (so map stays in same place)
    std::cout << CSI << "3L";

    // This section is to: See how to input a single letter or "char" as input.
    // If the input isn't alphanumeric (abcd...xyz), then we have an error.
    std::cout << INDENT << "What is the first letter of your name? " << INDENT << YELLOW;
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin >> firstLetterOfName;
    std::cout << RESET_COLOR << std::endl;

    if (std::cin.fail() || !isalpha(firstLetterOfName)) {
        std::cout << INDENT << "You ahve failed the second challenge and are eaten by a grue." << std::endl;
    }
    else {
        std::cout << INDENT << "You entered " << firstLetterOfName << std::endl;
    }
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get(); //press enter...

    //move cursor to the start of the 1st question
    //then delete & insert 4 lines
    std::cout << RESTORE_CURSOR_POS << CSI << "A" << CSI << "4M" << CSI << "4L";
    // This section: determins the health of the player based on their height and fraction of their first letter value.
    // The first letter of their name is able to be calc'd as a number because of ASCII values.
    if (firstLetterOfName != 0) {
        avatarHP = (float)height / (firstLetterOfName * 0.2f);
    }
    else {
        avatarHP = 0;
    }
    std::cout << INDENT << "Using a complex deterministic algorithm, it has been calculated that you have " << avatarHP << " hit point(s)." << std::endl;
    
    //These lines add's a pause before exiting the console. (waits for a user input)
    std::cout << std::endl << INDENT << "Press 'Enter' to exit the program." << std::endl;
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
    
    
    return;
}