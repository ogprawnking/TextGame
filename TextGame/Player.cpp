#include "Player.h"
#include  "GameDefines.h"
#include <iostream>


Player::Player() : m_mapPosition{ 0,0 }
{
	// changed values to uniform initialised list
}

Player::Player(int x, int y) : m_mapPosition{ x, y }
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


