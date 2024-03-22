#pragma once
#include "Point2D.h"

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

	bool executeCommand(int command);

private:
	void waitForInput();

private:
	Point2D m_mapPosition;
	int m_type;
};

