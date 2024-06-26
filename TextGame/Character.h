#pragma once
#include "GameObject.h"
#include <vector>

class Powerup;

class Character : public GameObject {
public:
	Character();
	Character(Point2D position, int health, int attack, int defend);
	~Character();

	void addPowerup(Powerup* pPowerup);

	virtual void draw() = 0;
	virtual void drawDescription() = 0;
	virtual void lookAt() = 0;

	int getHP() { return m_healthPoints; }
	int getAT() { return m_attackPoints; }
	int getDF() { return m_defendPoints; }
	bool isAlive() { return (m_healthPoints > 0); }

protected: // only this class can access
	std::vector<Powerup*> m_powerups;

	//instantiate variables
	int m_healthPoints;
	int m_attackPoints;
	int m_defendPoints;
};
