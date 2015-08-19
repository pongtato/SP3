#include "Character_Player.h"

CCharacter_Player* CCharacter_Player::mInstance = 0;

CCharacter_Player* CCharacter_Player::GetInstance()
{
	if (mInstance == 0)
		mInstance = new CCharacter_Player();

	return mInstance;
}

CCharacter_Player::CCharacter_Player(void)
{
}


CCharacter_Player::~CCharacter_Player(void)
{
}

void CCharacter_Player::setMesh(PLAYER_TYPE newMesh)
{
	m_playerMesh = newMesh;
}
void CCharacter_Player::setAmmoType(PLAYER_AMMO_TYPE newAmmoType)
{
	m_weaponChoice = newAmmoType;
}
void CCharacter_Player::setNewState(PLAYER_CURRENT_STATE newState)
{
	m_playerState = newState;
}
int CCharacter_Player::getMesh()
{
	return m_playerMesh;
}
int CCharacter_Player::getAmmoType()
{
	return m_weaponChoice;
}
int CCharacter_Player::getState()
{
	return m_playerState;
}

void CCharacter_Player::moveUp()
{
	m_acceleration.y += m_MoveSpeed;
}
void CCharacter_Player::moveDown()
{
	m_acceleration.y -= m_MoveSpeed;
}
void CCharacter_Player::moveLeft()
{
	m_acceleration.x -= m_MoveSpeed;
}
void CCharacter_Player::moveRight()
{
	m_acceleration.x += m_MoveSpeed;
}

