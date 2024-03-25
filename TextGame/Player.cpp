#define _CRT_SECURE_NO_WARNINGS


#include "Player.h"
#include  "GameDefines.h"
#include <iostream>
#include <algorithm>
#include "Room.h"
#include "Powerup.h"



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
	//descruct any powerups attached to player after it's picked up into inventory
	for (auto it = m_powerups.begin(); it != m_powerups.end(); it++) {
		delete* it;
	}
	m_powerups.clear();
}

void Player::addPowerup(Powerup* pPowerup)
{
	m_powerups.push_back(pPowerup);

	std::sort(m_powerups.begin(), m_powerups.end(), Powerup::compare);
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
		std::cout << (*it)->getName() << "\t";
	}
	std::cout << "\n" << std::endl;
}

bool Player::executeCommand(int command)
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
	}
	return false; //if none of these commands
}


