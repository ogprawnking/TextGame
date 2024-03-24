#pragma once
#include "Point2D.h"
#include "Powerup.h"
#include <vector>

class Player
{
public:
	Player();
	Player(int x, int y);
	~Player();

	void setPosition(Point2D position); //set x, y pos

	Point2D getPosition(); // get x, y pos

	void draw(); // draw player on map
	void drawInventory(); // draws inventory on screen

	bool executeCommand(int command, int roomType);
	
private:
	bool pickup(int roomType);

private:
	Point2D m_mapPosition;

	std::vector<Powerup> m_powerups;

	int m_healthPoints;
	int m_attackPoints;
	int m_defencePoints;
};

