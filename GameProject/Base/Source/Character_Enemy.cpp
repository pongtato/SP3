#include "Character_Enemy.h"


CCharacter_Enemy::CCharacter_Enemy(void)
{
	m_ScanTimer = (float)ScanDuration;
	PATHFIND = new CPathfinding;
	pathfind_tilemap = new TileMap;
	m_CurrentNode = 0;
	MoveDelay = MovementDelay;
	InLineOfSight = false; 
}


CCharacter_Enemy::~CCharacter_Enemy(void)
{
	delete PATHFIND;
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

bool CCharacter_Enemy::detectPlayer(Vector3 playerPos, TileMap* tileMap)
{
	m_RotationArcMax = getRotation() + FOVArc;
	m_RotationArcMin = getRotation() - FOVArc;

	Vector3 CornerLVel;
	Vector3 CornerRVel;
	CornerLVel.Set(cosf(Math::DegreeToRadian(m_RotationArcMin)),sinf(Math::DegreeToRadian(m_RotationArcMin)),getPosition().z);
	CornerRVel.Set(cosf(Math::DegreeToRadian(m_RotationArcMax)),sinf(Math::DegreeToRadian(m_RotationArcMax)),getPosition().z);

	DetectionCornerL = getPosition() + (CornerLVel * ((float)FOVdistance/2.f) );
	DetectionCornerR = getPosition() + (CornerRVel * ((float)FOVdistance/2.f) );
	DetectionCornerM = (getPosition() + (CornerRVel * (float)FOVdistance)) + (DetectionCornerL - DetectionCornerR) ;

	// check if within range
	if ( (playerPos - getPosition()).Length() <= FOVdistance )
	{
		//Check if within arc
		float tempAngle = Math::RadianToDegree(atan2f(playerPos.y - getPosition().y,playerPos.x - getPosition().x));
		
		if ( tempAngle <= 0 )
		{
			tempAngle += 360;
		}

		if ( tempAngle <= m_RotationArcMax && tempAngle >= m_RotationArcMin )
		{
			//cout << " Detected at " << tempAngle << " Expected: " << m_RotationArcMax << "," << m_RotationArcMin << endl;
			
			//Get direction from enemy to player
			LineOfSight = (playerPos - getPosition()).Normalized();
			return true;
		}
		else
		{
			//cout << " Not Detected" << tempAngle << " Expected: " << m_RotationArcMax << "," << m_RotationArcMin << endl;
			return false;
		}
	}
	return false;
}

void CCharacter_Enemy::Strategy_Chaseplayer(Vector3 playerPos,TileMap* tileMap)
{
	Vector3 temp = (TargetPosition - getPosition()).Normalized() * MoveSpeed;
	if ( m_weaponChoice != CAMERA && (TargetPosition - getPosition()).Length() > 1.5f )
	{		
		setVelocity(temp.x,temp.y,0);
	}
	else
	{
		setVelocity(0,0,0);
	}

	if ((TargetPosition - getPosition()).Length() > 1.5f)
	{
		setRotation(Math::RadianToDegree(atan2f(temp.y,temp.x)));
		if ( getRotation() <= 0 )
		{
			setRotation(getRotation() + 360);
		}	
	}
	else if ( m_weaponChoice != CAMERA && !detectPlayer(playerPos,tileMap))
	{

		resetTimer();
			setRotateDirection(playerPos);
		setNewState(SCANNING);
	}

	if ( m_weaponChoice == CAMERA )
	{
		if ( !detectPlayer(playerPos,tileMap) )
		{
			setNewState(SCANNING);
		}
	}
}

void CCharacter_Enemy::Strategy_Return(void)
{
	Vector3 temp = (getInitPosition() - getPosition()).Normalized() * MoveSpeed;
	setVelocity(temp.x,temp.y,0);
	setRotation(Math::RadianToDegree(atan2f(temp.y,temp.x)));
	
	if ( (getInitPosition() - getPosition()).Length() < 0.2f )
	{
		setRotation(getRotation() - 180);
		setVelocity(0,0,0);
		setNewState(IDLE);

	}

	if ( getRotation() <= 0 )
	{
		setRotation(getRotation() + 360);
	}
}

void CCharacter_Enemy::Strategy_Scan(double dt)
{
	if ( getRotation() >= 360 )
	{
		setRotation(0);
	}
	else if (  getRotation() <= 0 )
	{
		setRotation(360);
	}

	switch (m_RotateDirection)
	{
	case 0:
		{
			setRotation(getRotation() - (float)dt * ScanSpeed);
		}
		break;
	case 1:
		{
			setRotation(getRotation() + (float)dt * ScanSpeed);
		}
		break;
	}

	if ( getRotation() > (m_MedianRotation + ScanArc) )
	{
		m_RotateDirection = false;
	}

	if ( getRotation() < (m_MedianRotation - ScanArc) )
	{
		m_RotateDirection = true;
	}

	if ( m_ScanTimer > 0.0f )
	{
		m_ScanTimer -= (float)dt;
	}
	else if ( m_weaponChoice != CAMERA )
	{
		setNewState(TRACKING);
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

void CCharacter_Enemy::setRotateDirection(Vector3 playerPos)
{
	if ( (playerPos - DetectionCornerL).Length() < (playerPos - DetectionCornerR).Length() )
	{
		m_RotateDirection = false;
	}
	else 
	{
		m_RotateDirection = true;
	}
	m_MedianRotation = getRotation();
}

void CCharacter_Enemy::Strategy_Stalk(Vector3 playerPos,TileMap* tileMap)
{
	if (TargetPosition != playerPos )
	{
		m_CurrentNode = 0;
		PathFound = PATHFIND->FindPath(getPosition(),playerPos,tileMap);
		TargetPosition = playerPos;
		PATHFIND->hasFound = false;
	}

	if ( !PATHFIND->hasFound )
	{
		if ( PathFound.size() > 0 )
		{
			Vector3 temp = (PathFound[m_CurrentNode]->m_WorldPosition - getPosition()).Normalized() * MoveSpeed;
			setVelocity(temp.x,temp.y,0);

			if ( (PathFound[m_CurrentNode]->m_WorldPosition - getPosition()).Length() < 0.1f )
			{
				if ( m_CurrentNode < PathFound.size() - 1 )
				{
					m_CurrentNode++;
				}
				else
				{
					PATHFIND->hasFound = true;
				}
			}
		}
	}
	else
	{
		setVelocity(0,0,0);
		resetTimer();
		setRotateDirection(playerPos);
		setNewState(IDLE);
	}
}

void CCharacter_Enemy::UpdateEnemyPosition(double dt)
{
	Vector3 tempPos = getPosition();
	tempPos += getVelocity() * (float)dt;
	setPosition(tempPos.x,tempPos.y,getPosition().z);
}

void CCharacter_Enemy::CreateGrid(void)
{
	PATHFIND->Init(pathfind_tilemap);
}

Vector3 CCharacter_Enemy::getTargetPosition(void)
{
	return TargetPosition;
}

void CCharacter_Enemy::setTargetPosition(Vector3 newTarget)
{
	TargetPosition = newTarget;
}

void CCharacter_Enemy::resetTimer(void)
{
	m_ScanTimer = ScanDuration;
}