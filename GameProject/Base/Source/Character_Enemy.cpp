#include "Character_Enemy.h"


CCharacter_Enemy::CCharacter_Enemy(void)
{
	m_ScanTimer = (float)ScanDuration;
	PATHFIND = new CPathfinding;
	pathfind_tilemap = new TileMap;
	m_CurrentNode = 0;
	MoveDelay = MovementDelay;
	InLineOfSight = false;
	m_enemyState = IDLE;
	m_RotateDirection = false;
	delayTicking = false;
	m_RotationCompare = 0.f;
	AttackSpeed = 1.0f;
	FireCooldown = 0.0f;

	m_enemyHP = 100;

	TrackTimer = 0.0f;
	TrackTimerReset = 3.0f;
}


CCharacter_Enemy::~CCharacter_Enemy(void)
{
	delete PATHFIND;
}
void CCharacter_Enemy::ResetCooldown(void)
{
	FireCooldown = AttackSpeed;
}
float CCharacter_Enemy::getFirecooldown(void)
{
	return FireCooldown;
}
void CCharacter_Enemy::FireCooldownTick(float time)
{
	FireCooldown -= time;
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
void CCharacter_Enemy::setEnemyHP(int enemyHealth)
{
	m_enemyHP = enemyHealth;
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
int CCharacter_Enemy::getEnemyHP()
{
	return m_enemyHP;
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

		if ( tempAngle < 0 )
		{
			tempAngle += 360;
		}
		if ( tempAngle > 360 )
		{
			tempAngle -= 360;
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
	
}

void CCharacter_Enemy::Strategy_Return(void)
{
	
}

void CCharacter_Enemy::Strategy_Track(double dt)
{
	if ( m_weaponChoice != CAMERA )
	{
		Vector3 tempDirection = ( getTargetPosition() - getPosition());
		setRotation(Math::RadianToDegree(atan2f(tempDirection.y,tempDirection.x)));

		if ( getRotation() < 0 )
		{
			setRotation(getRotation() + 360);
		}
		if ( getRotation() > 360 )
		{
			setRotation(getRotation() - 360);
		}
	}
}

void CCharacter_Enemy::Strategy_Scan(double dt)
{
	if ( getRotation() < 0 )
	{
		setRotation(getRotation() + 360);
	}
	if ( getRotation() > 360 )
	{
		setRotation(getRotation() - 360);
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
		setNewState(RUNNING);
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

bool CCharacter_Enemy::Strategy_Pathfind(Vector3 playerPos,TileMap* tileMap)
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
			Vector3 temp = (PathFound[m_CurrentNode]->m_WorldPosition - getPosition()).Normalized() * MoveSpeed * PathfindMS_multiplier;
			setVelocity(temp.x,temp.y,0);
			setRotation(Math::RadianToDegree(atan2f(temp.y,temp.x)));

			if ( getRotation() < 0 )
			{
				setRotation(getRotation() + 360);
			}
			if ( getRotation() > 360 )
			{
				setRotation(getRotation() - 360);
			}

			if ( (PathFound[m_CurrentNode]->m_WorldPosition - getPosition()).Length() < 0.05f )
			{
				if ( m_CurrentNode < PathFound.size() - 1 )
				{
					setPosition(PathFound[m_CurrentNode]->m_WorldPosition.x,PathFound[m_CurrentNode]->m_WorldPosition.y,getPosition().z);
					m_CurrentNode++;
				}
				else
				{
					PATHFIND->hasFound = true;
					if ( getRotation() < 0 )
					{
						setRotation(getRotation() + 360);
					}
					if ( getRotation() > 360 )
					{
						setRotation(getRotation() - 360);
					}
					return true;
				}
			}
		}
	}
	return false;
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

void CCharacter_Enemy::setPatrolState(PATROL_MOVE_STATE newState)
{
	m_patrolState = newState;
}

int CCharacter_Enemy::getPatrolState(void)
{
	return m_patrolState;
}

void CCharacter_Enemy::Strategy_Patrol(double dt)
{
	switch (m_patrolState)
	{
	case PATROL_DOWN:
		{
			setVelocity(0,-MoveSpeed * float(dt) * 50.f,0);
			break;
		}
	case PATROL_LEFT:
		{
			setVelocity(-MoveSpeed * float(dt)* 50.f,0,0);
			break;
		}
	case PATROL_RIGHT:
		{
			setVelocity(MoveSpeed * float(dt)* 50.f,0,0);
			break;
		}
	case PATROL_UP:
		{
			setVelocity(0,MoveSpeed * float(dt)* 50.f,0);
			break;
		}
	}

	setRotation(Math::RadianToDegree(atan2f(getVelocity().y,getVelocity().x)));

	if ( getRotation() < 0 )
	{
		setRotation(getRotation() + 360);
	}
	if ( getRotation() > 360 )
	{
		setRotation(getRotation() - 360);
	}
}

void CCharacter_Enemy::setCameraState(CAMERA_SCAN_STATE newState)
{
	m_cameraState = newState;
}

int CCharacter_Enemy::getCameraState(void)
{
	return m_cameraState;
}

void CCharacter_Enemy::Strategy_Camera(double dt)
{
	float LimitL = 0;
	float LimitR = 0;

	if ( getRotation() < 0 )
	{
		setRotation(getRotation() + 360);
	}
	if ( getRotation() > 360 )
	{
		setRotation(getRotation() - 360);
	}

	switch (m_RotateDirection)
	{
	case 0:
		{
			// Camera is not in delay
			if ( !delayTicking )
			{
				setRotation(getRotation() - (float)dt * ScanSpeed);
				m_RotationCompare -= (float)dt * ScanSpeed;
			}
		}
		break;
	case 1:
		{
			// Camera is not in delay
			if ( !delayTicking )
			{
				setRotation(getRotation() + (float)dt * ScanSpeed);
				m_RotationCompare += (float)dt * ScanSpeed;
			}
		}
		break;
	}

	if ( m_RotationCompare >= ScanArc )
	{
		delayTicking = true;
		
		if ( delayTicking )
		{
			m_CameraDelay -= float(dt);
			if ( m_CameraDelay <= 0.0f )
			{
				// switch direction
				m_RotateDirection = false;
				m_CameraDelay = m_CameraDelayReset;
				delayTicking = false;
			}
		}
	}

	if ( m_RotationCompare <= -ScanArc )
	{
		delayTicking = true;
		
		if ( delayTicking )
		{
			m_CameraDelay -= float(dt);
			if ( m_CameraDelay <= 0.0f )
			{
				// switch direction
				m_RotateDirection = true;
				m_CameraDelay = m_CameraDelayReset;
				delayTicking = false;
			}
		}
	}
}

void CCharacter_Enemy::setCameraDelay(float newDelay)
{
	m_CameraDelay = newDelay;
	m_CameraDelayReset = newDelay;
}


void CCharacter_Enemy::ReduceTrackTimer(float timer)
{
	TrackTimer -= timer;
}

void CCharacter_Enemy::ResetTrackTimer(void)
{
	TrackTimer = TrackTimerReset;
}

float CCharacter_Enemy::getTrackTimer(void)
{
	return TrackTimer;
}