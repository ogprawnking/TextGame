#include "Food.h"
#include "GameDefines.h"
#include <iostream>

Food::Food() : m_healthPoints{ 10 }
{
	m_priority = PRIORITY_FOOD;
};

Food::Food(Point2D position) : GameObject{ position }, m_healthPoints{ 10 }
{
	m_priority = PRIORITY_FOOD;
};

void Food::draw() {
	std::cout << FOOD_TILE;
}

void Food::drawDescription() {
	std::cout << INDENT << "You see a box of... DONUTS! YUM!" << std::endl;
}

void Food::lookAt() {
	std::cout << INDENT << "There seems to be something edible here."
		<< std::endl;
}
