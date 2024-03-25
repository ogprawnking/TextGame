#pragma once
#include "Point2D.h"
#include "Powerup.h"
#include <vector>

class Room;

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

	bool executeCommand(int command, Room* pRoom);
	
private:
	bool pickup(Room* room);

private:
	Point2D m_mapPosition;

	std::vector<Powerup> m_powerups;

	int m_healthPoints;
	int m_attackPoints;
	int m_defencePoints;
};

