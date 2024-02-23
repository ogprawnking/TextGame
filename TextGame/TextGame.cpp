#include <iostream>

void main()
{
    int height = 0;

    std::cout << "Welcome to The Game!" << std::endl;
    std::cout << "A game of adventure, danger, and low cunning." << std::endl;
    std::cout << "It's definitely not related to any other text-based adventure game." << std::endl;

    std::cout << "First, some questions..." << std::endl;
    std::cout << "How tall are you, in centimeters? " << std::endl;

    std::cin >> height;
    std::cin.clear();   //clears any data inside the input buffer
    std::cin.ignore(std::cin.rdbuf()->in_avail()); /*needs argument that tells how many characters to ignore.
    Therefore cin.rdbuf()->in_avail() read how many characters remain in buffer and pass valuye to cin.ignore().*/

    std::cout << "You entered " << height << std::endl;
    // THIS LINE IS TO  TEST THE GIT FEATURE IN VISUAL STUDIO

    //These lines add's a pause before exiting the console. (waits for a user input)
    std::cout << std::endl << "Press 'Enter' to exit the program." << std::endl;
    std::cin.get();
    return;
}
