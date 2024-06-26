#define _CRT_SECURE_NO_WARNINGS
//#include <cstring>
#include <iostream>
#include "String.h"

#include "GameDefines.h"
#include "Powerup.h"

Powerup::Powerup() : m_healthMultiplier{ 1 }, m_attackMultiplier{ 1 }, m_defenceMultiplier{ 1 }
{
	m_priority = PRIORITY_POWERUP;
	m_name[0] = 0;
}

Powerup::Powerup(const char name[30], float health, float attack, float defence)
{
	// set name
	m_priority = PRIORITY_POWERUP;
	strcpy(m_name, name);

	/*m_healthMultiplier = health;
	m_attackMultiplier = attack;
	m_defenceMultiplier = defence;*/
}

Powerup::~Powerup()
{
}

char* Powerup::getName()
{
	return m_name;
}

float Powerup::getHealthMultiplier()
{
	return m_healthMultiplier;
}

float Powerup::getAttackMultiplier()
{
	return m_attackMultiplier;
}

float Powerup::getDefenceMultiplier()
{
	return m_defenceMultiplier;
}

void Powerup::setName(const char* pStr)
{
	strncpy(m_name, pStr, 30);
}

bool Powerup::compare(const Powerup* p1, const Powerup* p2)
{
	// compares powerup name and sorts them based on each char (as numbers)
	return (strcmp(p1->m_name, p2->m_name) < 0) ? true : false;
}

void Powerup::draw() {
	std::cout << TREASURE_TILE;
}
void Powerup::drawDescription() {
	std::cout << INDENT << "There appears to be some treasure here. Perhaps you should investigate futher?." << std::endl;
}
void Powerup::lookAt() {
	std::cout << INDENT << "There is some treasure here. It looks small enough to pick up." << std::endl;
}
