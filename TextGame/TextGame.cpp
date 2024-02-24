#include <iostream>
#include <windows.h>

const char* ESC = "x1b";
const char* CSI = "\x1b[";

const char* TITLE = "\x1b[5;20H";
const char* INDENT = "\x1b[5C";
const char* YELLOW = "\x1b[93m";
const char* MAGENTA = "\x1b[95m";
const char* RESET_COLOR = "\x1b[0m";
const char* SAVE_CURSOR_POS = "\x1b[s";
const char* RESTORE_CURSOR_POS = "\x1b[u";


void main()
{

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

    std::cout << TITLE << MAGENTA << "welcome to GAME!" << RESET_COLOR << std::endl;
    std::cout << INDENT << "A game of adventure, danger, and low cunning." << std::endl;
    std::cout << INDENT << "It's definitely not related to any other text-based adventure game." << std::endl;
    std::cout << "First, some questions..." << std::endl;
    // saving cursor position
    std::cout << SAVE_CURSOR_POS;
    std::cout << INDENT << "How tall are you, in centimeters? " << INDENT << YELLOW;

    std::cin >> height;
    std::cout << RESET_COLOR << std::endl;

    if (std::cin.fail()) { 
    //fail() func = true if wrong data type entered into input.
        std::cout << INDENT << "You have failed the first challenge and are eaten by a grue.";
    }
    else {
        std::cout << INDENT << "You entered " << height << std::endl;
    }
    std::cin.clear();   //clears any data inside the input buffer
    std::cin.ignore(std::cin.rdbuf()->in_avail()); /*needs argument that tells how many characters to ignore.
    Therefore cin.rdbuf()->in_avail() reads how many characters remain in buffer and pass valuye to cin.ignore().*/
    std::cin.get(); // Typically used for enter key, so that the game doesn't go through too fast. (Needs no input inside buffer)

    //move the cursor to the start of the 1st question
    std::cout << RESTORE_CURSOR_POS;
    // THEN delete the next 4 lines of text
    std::cout << CSI << "4M";

    // This section is to: See how to input a single letter or "char" as input.
    // If the input isn't alphanumeric (abcd...xyz), then we have an error.
    std::cout << INDENT << "What is the first letter of your name? " << INDENT << YELLOW;

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
    std::cout << RESTORE_CURSOR_POS;
    std::cout << CSI << "A";    // cursor up 1
    std::cout << CSI << "4M";   // delete the next 4 lines of text

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
    std::cin.get();
    return;
}
