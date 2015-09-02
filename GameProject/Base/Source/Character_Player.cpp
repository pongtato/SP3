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
	m_weaponChoice = PISTOL;
	m_playerState = IDLE;
	walkLimit = 0;
	m_HasBeenDetected = false;
	m_AlertState = UNDETECTED;
}


CCharacter_Player::~CCharacter_Player(void)
{
	delete mInstance;
}

void CCharacter_Player::setMesh(PLAYER_TYPE newMesh)
{
	m_playerMesh = newMesh;
}
void CCharacter_Player::setAmmoType(int ammoTypeID)
{
	switch ( ammoTypeID )
	{
	case 0:
		m_weaponChoice = PISTOL;
		break;
	case 1:
		m_weaponChoice = MG;
		break;
	case 2:
		m_weaponChoice = SHOTGUN;
		break;
	}
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

void CCharacter_Player::ManipulateDetectionLevel(float toAddTo)
{
	m_DetectionLevel = Math::Clamp(m_DetectionLevel + toAddTo,0.f,99.f);
	//m_DetectionLevel += toAddTo;

	if ( m_DetectionLevel >= DETECTIONMAX && !DetectionFading)
	{
		setNewAlertState(DETECTED);
		m_DetectionLevel = DETECTIONMAX;
	}

	if ( m_DetectionLevel <= 0 )
	{
		switch ( m_AlertState )
		{
		case DETECTED:
			setNewAlertState(CAUTION);
			m_HasBeenDetected = false;
			m_DetectionLevel = DETECTIONMAX;
			break;
		case CAUTION:
			setNewAlertState(UNDETECTED);
			m_DetectionLevel = DETECTIONMAX;
			break;
		default :
			m_DetectionLevel = 0;
		}
	}
}

float CCharacter_Player::getDetectionLevel(void)
{
	return m_DetectionLevel;
}

void CCharacter_Player::SetDetected(bool TF)
{
	m_HasBeenDetected = TF;
}

bool CCharacter_Player::getDetected(void)
{
	return m_HasBeenDetected;
}

void CCharacter_Player::setNewAlertState(ALERT_STATE newState)
{
	m_AlertState = newState;
}

CCharacter_Player::ALERT_STATE CCharacter_Player::getAlertState(void)
{
	return m_AlertState;
}

void CCharacter_Player::ResetTimer(void)
{
	m_DetectionFadeTimer = RESETTIMER;
	DetectionFading = false;
}

void CCharacter_Player::ManipulateDetectionFadeTimer(float toAddTo)
{
	m_DetectionFadeTimer += toAddTo;

	if ( m_DetectionFadeTimer <= 0 )
	{
		DetectionFading = true;
	}
}

float CCharacter_Player::getDetectionFadeTimer(void)
{
	return m_DetectionFadeTimer;
}