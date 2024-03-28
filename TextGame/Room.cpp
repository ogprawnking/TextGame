#define _CRT_SECURE_NO_WARNINGS

#include "String.h" // Custom String class

#include <iostream>
#include <algorithm>

#include "GameObject.h"
#include "Enemy.h"
#include "Room.h"
#include "GameDefines.h"
#include "Powerup.h"
//#include "Player.h"
#include "Food.h"


Room::Room() : m_type{ EMPTY }, m_mapPosition{ 0, 0 }
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

// add object to the vector of objects
void Room::addGameObject(GameObject* object)
{
	m_objects.push_back(object);
	std::sort(m_objects.begin(), m_objects.end(), GameObject::compare);
}

// remove object from vector
void Room::removeGameObject(GameObject* object)
{
	for (auto it = m_objects.begin(); it != m_objects.end(); it++) {
		if (*it == object) {
			m_objects.erase(it);
			return;
		}
	}
}

int Room::getType()
{
	return m_type;
}

void Room::draw()
{
	switch (m_type)
	{
		// list is much shorter, this applies room type to the room
	case EMPTY:
		// assume first object in vector takes priority
		if (m_objects.size() > 0)
			m_objects[0]->draw();
		else
			std::cout << EMPTY_TILE;
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
		// checks if room has objects and makes description.
		if (m_objects.size() > 0)
			m_objects[0]->drawDescription();
		else
		std::cout << INDENT << "You're in a meadow of grass. It's quite tranquil here." << std::endl;
		break;
	case ENTRANCE:
		std::cout << INDENT << "The entrance you used to enter this maze is blocked. There is no going back." << std::endl;
		break;
	case EXIT:
		std::cout << INDENT << "You see an out! Time to go home." << std::endl;
		break;
	}
}

// check room for objects and output them
void Room::lookAt()
{
	if (m_objects.size() > 0)
		m_objects[0]->lookAt();
	else
		std::cout << "You look around, but see nothing worth mentioning" << std::endl;
}

// if no enemy in room return nullptr
Enemy* Room::getEnemy()
{
	for (GameObject* pObj : m_objects) {
		Enemy* enemy = dynamic_cast<Enemy*>(pObj);
		if (enemy != nullptr)
			return enemy;
	}
	return nullptr;
}

// if no powerup return nullptr
Powerup* Room::getPowerup()
{
	for (GameObject* pObj : m_objects) {
		Powerup* powerup = dynamic_cast<Powerup*>(pObj);
		if (powerup != nullptr)
			return powerup;
	}
	return nullptr;
}

// if no food return nullptr
Food* Room::getFood()
{
	for (GameObject* pObj : m_objects) {
		Food* food = dynamic_cast<Food*>(pObj);
		if (food != nullptr)
			return food;
	}
	return nullptr;
}
