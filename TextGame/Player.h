#pragma once
#include "Point2D.h"

class Player
{
public:
	Player();
	Player(int x, int y); // OverLCnstr for player position
	~Player();

	void setPosition(Point2D position); //set x, y pos

	Point2D getPosition(); // get x, y pos

	void draw(); // draw player on map

	bool executeCommand(int command);

private:
	Point2D m_mapPosition;
};

