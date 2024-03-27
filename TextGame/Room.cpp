#define _CRT_SECURE_NO_WARNINGS

#include "String.h" // Custom String class

#include <iostream>

#include "Room.h"
#include "GameDefines.h"
#include "Powerup.h"
#include "Player.h"
#include "Food.h"


Room::Room() : m_type(EMPTY), m_mapPosition{ 0,0 }, m_powerup{ nullptr }, m_enemy{ nullptr }, m_food{ nullptr}
{
}

Room::~Room()
{
}

void Room::setPosition(Point2D position)
{
	m_mapPosition = position;
}

void Room::setType(int type)
{
	m_type = type;
}

int Room::getType()
{
	return m_type;
}

void Room::draw()
{
	switch (m_type)
	{
	case EMPTY:
		if (m_enemy != nullptr) {
			std::cout << ENEMY_TILE;
			break;
		}
		if (m_powerup != nullptr) {
			std::cout << TREASURE_TILE;
			break;
		}
		if (m_food != nullptr) {
			std::cout << FOOD_TILE;
			break;
		}
		std::cout << EMPTY_TILE;
		break;
	case ENEMY:
		std::cout << ENEMY_TILE;
		break;
	case TREASURE_HP:
	case TREASURE_ATT:
	case TREASURE_DEF:
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

void Room::drawDescription() // used to describe current room
{
	switch (m_type) {
	case EMPTY:
		// check if an "EMPTY (Default) room" has an enemy, treasure or food (using pointers)
		if (m_enemy != nullptr) {
			std::cout << INDENT << "BEWARE. An enemy is approaching." << std::endl;
			break;
		}
		if (m_powerup != nullptr) {
			std::cout << INDENT << "Your journey has been rewarded. You have found some treasure" << std::endl;
			break;
		}
		if (m_food != nullptr) {
			std::cout << INDENT << "At last! You collect some food to sustain you on your journey." << std::endl;
			break;
		}
		std::cout << INDENT << "You are in an empty meadow. There is nothing of note here." << std::endl;
		break;
	case ENTRANCE:
		std::cout << INDENT << "The entrance you used to enter this maze is blocked. There is no going back." << std::endl;
		break;
	case EXIT:
		std::cout << INDENT << "Despite all odds, you made it to the exit. Congratulations." << std::endl;
		break;
	}
}