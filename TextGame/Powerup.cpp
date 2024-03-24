#define _CRT_SECURE_NO_WARNINGS

#include "Powerup.h"
#include "String.h"

Powerup::Powerup(const char name[30], float health, float attack, float defence)
{
	// set name
	strcpy(m_name, name);

	m_healthMultiplier = health;
	m_attackMultiplier = attack;
	m_defenceMultiplier = defence;
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
