#pragma once
#include "Point2D.h"

class Powerup;
class Player;

class Room
{
public:
	Room(); // default constructor
	~Room(); // destructor

	void setPosition(Point2D position);
	void setType(int type);

	int getType();

	void draw();
	void drawDescription();

	bool executeCommand(int command, Player*  pPlayer);

private:
	bool pickup(Player* pPlayer);
	void waitForInput();

private:
	Point2D m_mapPosition;
	int m_type;
	Powerup* m_powerup;
};

