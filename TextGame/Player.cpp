#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>

#include "Player.h"
#include "GameDefines.h"

#include "Room.h"
#include "Powerup.h"
#include "Enemy.h"
#include "Food.h"

Player::Player() : Character({ 0, 0 }, 100, 20, 20)
{
	m_priority = PRIORITY_PLAYER;
}


Player::Player(int x, int y) : Character({ x, y }, 100, 20, 20)
{
	// changed to uniform initialised list: overLConstr for altering x,y m_mapPositions
}

Player::~Player()
{
}



void Player::draw()
{
	std::cout << PLAYER_TILE;
}

void Player::drawDescription()
{}

void Player::lookAt()
{
	std::cout << INDENT << "I'm still looking good!" << std::endl;
}

void Player::drawInventory()
{
	std::cout << INDENT;
	for (auto it = m_powerups.begin(); it < m_powerups.end(); it++)
	{
		std::cout << (*it)->getName() << "\t";
	}
	std::cout << "\n" << std::endl;
}

void Player::executeCommand(int command, Room* pRoom)
{
	switch (command) {
	case EAST:
		if (m_mapPosition.x < MAZE_WIDTH - 1) // if less than the far right side of map
			m_mapPosition.x++; // move right one spot
		return;
	case WEST:
		if (m_mapPosition.x > 0) // if more than far left side of map
			m_mapPosition.x--; // move left one spot
		return;
	case NORTH:
		if (m_mapPosition.y > 0) // if lower than top of map (larger Y number means position is lower)
			m_mapPosition.y--; // move them up one spot
		return;
	case SOUTH:
		if (m_mapPosition.y < MAZE_HEIGHT - 1) // if less than height (height number increases going down)
			m_mapPosition.y++; // move down one spot
		return;
	case LOOK:
		pRoom->lookAt();
		break;
	case FIGHT:
		attack(pRoom->getEnemy());
		break;
	case PICKUP:
		pickup(pRoom);
		break;
	default:
		// direction not valid,
		// do nothing, go back to top of loop and ask again.
		std::cout << INDENT << "You try, but you just can't do it." << std::endl;
		break;
	}
	std::cout << INDENT << "Press 'Enter' to continue.";
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
}

void Player::pickup(Room* pRoom)
{
	if (pRoom->getPowerup() != nullptr) {
		Powerup* powerup = pRoom->getPowerup();
		std::cout << INDENT << "You pick up the " << powerup->getName() << std::endl;
		// add powerup to player's inventory
		addPowerup(powerup);
		// remove powerup from room... DON'T delete it (the player OWNS it now!)
		pRoom->removeGameObject(powerup);

	}
	else if (pRoom->getFood() != nullptr) {
		Food* food = pRoom->getFood();
		// eat the food
		m_healthPoints += food->getHP();
		std::cout << INDENT << "You feel refreshed. Your health is now " << m_healthPoints << std::endl;
		// remove food from the room
		pRoom->removeGameObject(food);

	}
	else {
		std::cout << INDENT << "There is nothing here to pick up." << std::endl;
	}
}

void Player::attack(Enemy* pEnemy)
{
	if (pEnemy == nullptr) {
		std::cout << INDENT << "There is no one here you can fight with." << std::endl;
	}
	else {
		pEnemy->onAttacked(m_attackPoints);

		if (pEnemy->isAlive() == false) {
			std::cout << INDENT << "You fight a enemy and kill it." << std::endl;
		}
		else {
			int damage = pEnemy->getAT() - m_defencePoints;
			if (damage < 0)
				damage = 1 + rand() % 10;
			m_healthPoints -= damage;

			std::cout << INDENT << "You fight and take " << damage << " points damage. Your health is now at " << m_healthPoints << std::endl;
			std::cout << INDENT << "The enemy has " << pEnemy->getHP() << " health remaining." << std::endl;
		}
	}
}


