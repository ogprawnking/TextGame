#pragma once
#include "Point2D.h"
#include <vector>

class GameObject;
class Enemy;
class Powerup;
class Food;

class Room
{
public:
	Room(); // default constructor
	~Room(); // destructor

	void setPosition(Point2D position);
	void setType(int type);
	
	void addGameObject(GameObject* object);
	void removeGameObject(GameObject* object);

	//void setEnemy(Enemy* pEnemy) { m_enemy = pEnemy; }
	//void setPowerup(Powerup* pPowerup) { m_powerup = pPowerup; }	
	//void setFood(Food* pFood) { m_food = pFood; }

	int getType();
	//Enemy* getEnemy() { return m_enemy; }
	//Powerup* getPowerup() { return m_powerup; }		These are implemented elsewhere.
	//Food* getFood() { return m_food; }

	void draw();
	void drawDescription();

	void lookAt();
	// getter functions
	Enemy* getEnemy();
	Powerup* getPowerup();
	Food* getFood();

private:
	Point2D		m_mapPosition;
	int			m_type;
	/*Powerup*	m_powerup;
	Enemy*		m_enemy;		//the vector below takes care of this
	Food*		m_food;*/

	std::vector < GameObject*> m_objects; // vector to store multiple objects in a room
};

