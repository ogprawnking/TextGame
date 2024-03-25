#define _CRT_SECURE_NO_WARNINGS

#include "Room.h"
#include "GameDefines.h"
#include <iostream>
#include "Powerup.h"
#include "Player.h"
#include "String.h"


static const char itemNames[15][30] = {
	"indifference", "invisibility", "invulnerability", "incontinence",
	"improbability", "impatience", "indecision", "inspiration", "independence",
	"incurability", "integration", "invocation", "inferno", "indigestion",
	"inoculation"

};

Room::Room() : m_type(EMPTY), m_mapPosition{ 0,0 }, m_powerup{ nullptr }
{
}

Room::~Room()
{
	if (m_powerup != nullptr)
		delete m_powerup;
}

void Room::setPosition(Point2D position)
{
	m_mapPosition = position;
}

void Room::setType(int type)
{
	m_type = type;

	if (!(m_type == TREASURE_HP || m_type == TREASURE_ATT || m_type == TREASURE_DEF))
		return;
	if (m_powerup != nullptr)
		return;

	int item = rand() % 15;
	char name[30] = "";

	float HP = 1;
	float ATT = 1;
	float DEF = 1;

	switch (type) {
	case TREASURE_HP:
		strcpy(name, "potion of ");
		HP = 1.1f;
		break;
	case TREASURE_ATT:
		strcpy(name, "sword of ");
		ATT = 1.1f;
		break;
	case TREASURE_DEF:
		strcpy(name, "shield of ");
		DEF = 1.1f;
		break;
	}
	strncat(name, itemNames[item], 30);
	m_powerup = new Powerup(name, HP, ATT, DEF);
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
		std::cout << INDENT << "You are in an empty meadow. There is nothing of note here." << std::endl;
		break;
	case ENEMY:
		std::cout << INDENT << "BEWARE. An enemy is approaching." << std::endl;
		break;
	case TREASURE_HP:
	case TREASURE_ATT:
	case TREASURE_DEF:
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

bool Room::executeCommand(int command, Player* pPlayer)
{
	switch (command) {
	case LOOK:
		if (m_type == TREASURE_HP || m_type == TREASURE_ATT || m_type == TREASURE_DEF) {
			std::cout << INDENT << "There is some treasure here. It looks small enough to pickup." << std::endl;
		}
		else {
			std::cout << INDENT << "You look around, but see nothing worth mentioning" << std::endl;
		}
			std::cout << "Press 'Enter' to continue.";
		waitForInput(); //clear input buffer and wait for user to press 'any key'
		break;
	case FIGHT:
		std::cout << INDENT << "You could try and fight, but you don't have a weapon" << std::endl;
		std::cout << "Press 'Enter' to continue.";
		waitForInput(); //clear input buffer and wait for user to press 'any key'
		break;
	case PICKUP:
		return pickup(pPlayer);
	default:
		std::cout << INDENT << "You try, but you just can't do it..." << std::endl;
		std::cout << INDENT << "Press 'Enter' to continue.";
		waitForInput();
		break;
	}
	return false;
}

bool Room::pickup(Player* pPlayer)
{
	if (m_powerup == nullptr) {
		std::cout << INDENT << "There is nothing here to pick up." << std::endl;
		return true;
	}

	std::cout << INDENT << "You pick up the " << m_powerup->getName() << std::endl;

	//add powerup to player's inventory
	pPlayer->addPowerup(m_powerup);

	// remove powerup from the room
	// (but don't delete it, the player owns it now)
	m_powerup = nullptr;

	// change this room type to empty
	m_type = EMPTY;

	std::cout << INDENT << "Press 'Enter' to continue.";
	waitForInput();
	return true;
}

void Room::waitForInput()
{
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
}
