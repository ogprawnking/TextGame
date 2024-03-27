#include <iostream>
#include "Game.h"

// All functions and variables are in classes now!
// Just need to implement a loop for the game's draw and update classes/functions


void main() {
	Game game;
	
	// if we run startup() and returns false.. end program.
	if (game.startup() == false)
		return;

	/*
	while (!game.isGameOver())


	game.isGameOver = false;
	!game.isGameOver == true;
	while true == true;
	*/

	// game loop
	while (!game.isGameOver()) 
	/* '!' operator inverses the current logic of the function
	therefore if 'isGameOver' now returns false then the Game is now over!*/ 
	{
		game.draw();

		game.update();
		// end game loop
	}
	std::cout << std::endl << INDENT << "Press 'Enter' to exit the program";
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
}