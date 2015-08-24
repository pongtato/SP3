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

bool CCharacter_Enemy::detectPlayer(Vector3 playerPos)
{
	// check if within range
	if ( (playerPos - getPosition()).Length() < FOVdistance )
	{
		m_RotationArcMax = getRotation() + FOVArc;
		m_RotationArcMin = getRotation() - FOVArc;
		//Check if within arc
		float tempAngle = Math::RadianToDegree(atan2f(playerPos.y - getPosition().y,playerPos.x - getPosition().x));
		
		if ( tempAngle <= 0 )
		{
			tempAngle += 360;
		}
		
		if ( tempAngle <= m_RotationArcMax && tempAngle >= m_RotationArcMin )
		{
			cout << " Detected at " << tempAngle << " Expected: " << m_RotationArcMax << "," << m_RotationArcMin << endl;
			if ( m_weaponChoice != CAMERA )
			{
				m_enemyState = CHASING;
			}
			return true;
		}
		else
		{
			cout << " Not Detected" << tempAngle << " Expected: " << m_RotationArcMax << "," << m_RotationArcMin << endl;
			return false;
		}
	}
}

void CCharacter_Enemy::Strategy_Chaseplayer(Vector3 playerPos)
{
	if ( (getInitPosition() - getPosition()).Length() < ChaseDistance )
	{
		Vector3 temp = playerPos - getPosition();
		setVelocity(temp.x,temp.y,0);
	}
	else
	{
		setNewState(RUNNING);
	}
}

void CCharacter_Enemy::Strategy_Return(void)
{
	Vector3 temp = getInitPosition() - getPosition();
	setVelocity(temp.x,temp.y,0);
}

void CCharacter_Enemy::Strategy_Scan(bool Direction, double dt)
{
	switch (Direction)
	{
	case 0:
		{
			setRotation(getRotation() - (float)dt);
		}
		break;
	case 1:
		{
			setRotation(getRotation() + (float)dt);
		}
		break;
	}
}

void CCharacter_Enemy::setGroupID(int newGroupID)
{
	m_GroupID = newGroupID;
}

int CCharacter_Enemy::getGroupID(void)
{
	return m_GroupID;
}
