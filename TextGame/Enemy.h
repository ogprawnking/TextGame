#pragma once

#include "Point2D.h"
class Enemy
{
public:
	Enemy() : m_healthPoints{ 20 }, m_attackPoints{ 10 }, m_defendPoints{ 5 } {} // initialise hp, att, def of enemy
	~Enemy() {};

	void setPosition(const Point2D& position) { m_mapPosition = position; } // set map position
	Point2D getPosition() { return m_mapPosition; }; // get position on map

	int getHP() { return m_healthPoints; }
	int getATT() { return m_attackPoints; } // ^ v getHp from initiliased values
	int getDEF() { return m_defendPoints; }

	bool isAlive() { return (m_healthPoints > 0); } // isAlive = true if health_points more than 0

	void onAttacked(int attackPoints); // function to change variables when attacked. I.e. percentage to block attacks, use special defence powerups etc.

private:
	Point2D m_mapPosition;

	int m_healthPoints;
	int m_attackPoints;
	int m_defendPoints;


};

