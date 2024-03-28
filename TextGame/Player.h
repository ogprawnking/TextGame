#pragma once
#include "Point2D.h"
#include "Character.h"
#include <vector>

class Powerup;
class Room;
class Enemy;


class Player : public Character
{
public:
	Player();
	Player(int x, int y);
	~Player();

	//void addPowerup(Powerup* pPowerup);
	//void setPosition(const Point2D& position); // Only refer to the position
	//Point2D getPosition(); // get x, y pos

	void draw(); // draw player on map
	void drawInventory(); // draws inventory on screen
	void drawDescription();
	void lookAt();

	void executeCommand(int command, Room* pRoom);
	
	
//private:
	void pickup(Room* pRoom);
	void attack(Enemy* pEnemy);

//private:
//	Point2D m_mapPosition;
//
//	std::vector<Powerup*> m_powerups;
//
	int m_healthPoints;
	int m_attackPoints;
	int m_defencePoints;
};