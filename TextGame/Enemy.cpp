#include "Enemy.h"
#include "GameDefines.h"
#include <iostream>

Enemy::Enemy() : Character({ 0,0 }, 20, 10, 5)
{
	m_priority = PRIORITY_ENEMY;
}
void Enemy::onAttacked(int attackPoints) {
	m_healthPoints -= attackPoints - m_defendPoints;
	if (m_healthPoints < 0)
		m_healthPoints = 0;
}

void Enemy::draw() {
	std::cout << ENEMY_TILE;
}
void Enemy::drawDescription() {
	std::cout << INDENT << "BEWARE. An enemy is approaching." << std::endl;
}
void Enemy::lookAt() {
	std::cout << INDENT << "LOOK OUT! An enemy is approaching." << std::endl;
}
