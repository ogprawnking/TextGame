#define _CRT_SECURE_NO_WARNINGS


#include "Player.h"
#include  "GameDefines.h"
#include <iostream>
#include <algorithm>
#include "Room.h"


Player::Player() : m_mapPosition{ 0,0 }, m_healthPoints{ 100 }, m_attackPoints{ 20 }, m_defencePoints{ 20 }
{
	// changed values to uniform initialised list
}

Player::Player(int x, int y) : m_mapPosition{ x,y }, m_healthPoints{ 100 }, m_attackPoints{ 20 }, m_defencePoints{ 20 }
{
	// changed to uniform initialised list: overLConstr for altering x,y m_mapPositions
}

Player::~Player()
{
}

void Player::setPosition(Point2D position)
{
	m_mapPosition = position;
}

Point2D Player::getPosition()
{
	return m_mapPosition;
}

void Player::draw()
{
	std::cout << PLAYER_TILE;
}

void Player::drawInventory()
{
	std::cout << INDENT;
	for (auto it = m_powerups.begin(); it < m_powerups.end(); it++)
	{
		std::cout << (*it).getName() << "\t";
	}
	std::cout << "\n" << std::endl;
}

bool Player::executeCommand(int command, Room* room)
{
	switch (command) {
	case EAST:
		if (m_mapPosition.x < MAZE_WIDTH - 1) // if less than the far right side of map
			m_mapPosition.x++; // move right one spot
		return true;
	case WEST:
		if (m_mapPosition.x > 0) // if more than far left side of map
			m_mapPosition.x--; // move left one spot
		return true;
	case NORTH:
		if (m_mapPosition.y > 0) // if lower than top of map (larger Y number means position is lower)
			m_mapPosition.y--; // move them up one spot
		return true;
	case SOUTH:
		if (m_mapPosition.y < MAZE_HEIGHT - 1) // if less than height (height number increases going down)
			m_mapPosition.y++; // move down one spot
		return true;
	case PICKUP:
		return pickup(room); // pass roomType because it's only valid in that roomType

	}
	return false; //if none of these commands
}

bool Player::pickup(Room* room)
{
	static const char itemNames[15][30] = {
		"indifference", "invisibility", "invulnerability", "incontinence",
	"improbability", "impatience", "indecision", "inspiration", "independence",
	"incurability", "integration", "invocation", "inferno", "indigestion",
	"inoculation"
	};

	int item = rand() % 15; // choose random name of these 15 options
	char name[30] = ""; // a name can have 30 characters

	switch (room->getType()) {
	case TREASURE_HP:
		strcpy(name, "potion of ");
		break;
	case TREASURE_ATT:
		strcpy(name, "sword of ");
		break;
	case TREASURE_DEF:
		strcpy(name, "shield of ");
		break;
	default:
		return false;
	}

	//append item name to the string
	strncat(name, itemNames[item], 30); // (destination, _source, sizet _count)
	std::cout << INDENT << "You pick up the " << name << std::endl;
	m_powerups.push_back(Powerup(name, 1, 1, 1.1f));

	std::sort(m_powerups.begin(), m_powerups.end(), Powerup::compare);
	// set room to EMPTY after: pickup item, add to inventory and sort inventory.
	room->setType(EMPTY);

	std::cout << INDENT << "Press 'Enter' to continue.";
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
	return true;
}


