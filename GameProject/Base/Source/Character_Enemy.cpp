#include "Character_Enemy.h"


CCharacter_Enemy::CCharacter_Enemy(void)
{
}


CCharacter_Enemy::~CCharacter_Enemy(void)
{
}

void CCharacter_Enemy::setMesh(ENEMY_TYPE newMesh)
{
	m_enemyMesh = newMesh;
}
void CCharacter_Enemy::setAmmoType(ENEMY_AMMO_TYPE newAmmoType)
{
	m_weaponChoice = newAmmoType;
}
void CCharacter_Enemy::setNewState(EMEY_CURRENT_STATE newState)
{
	m_enemyState = newState;
}
int CCharacter_Enemy::getMesh()
{
	return m_enemyMesh;
}
int CCharacter_Enemy::getAmmoType()
{
	return m_weaponChoice;
}
int CCharacter_Enemy::getState()
{
	return m_enemyState;
}
