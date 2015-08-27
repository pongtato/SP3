#pragma once
#include "Character.h"
#include "Weapon.h"
#include "SoundManager.h"
#define DETECTIONMAX 99
#define RESETTIMER   5

class CCharacter_Player : public CCharacter
{
public:

	enum PLAYER_TYPE
	{
		PLAYER_MESH_1,
		PLAYER_MESH_2,
		PLAYER_MESH_3,
		PLAYER_MESH_4,
	};

	enum PLAYER_AMMO_TYPE
	{
		PISTOL,
		MG,
		SHOTGUN,
		ROCKET,
		GRENADE,
		AMMO_TOTAL,
	};

	enum PLAYER_CURRENT_STATE
	{
		IDLE,
		RUNNING,
		SHOOTING,
		FLASHED,
		STUNNED,
		WOUNDED,
		STATE_TOTAL,
	};

	enum ALERT_STATE
	{
		UNDETECTED,
		CAUTION,
		DETECTED,
		ALERT_STATE_TOTAL,
	};

	CCharacter_Player(void);
	~CCharacter_Player(void);

	void setMesh(PLAYER_TYPE newMesh);
	void setAmmoType(int ammoTypeID);
	void setNewState(PLAYER_CURRENT_STATE newState);
	void setNewAlertState(ALERT_STATE newState);
	ALERT_STATE getAlertState(void);


	int getMesh(void);
	int getAmmoType(void);
	int getState(void);

	static CCharacter_Player* GetInstance();
	CWeapon* Weapon;

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	void SetDetected(bool TF);
	bool getDetected(void);

	void ManipulateDetectionLevel(float toAddTo);
	float getDetectionLevel(void);
	void ResetTimer(void);
	void ManipulateDetectionFadeTimer(float toAddTo);
	float getDetectionFadeTimer(void);

	Vector3 TrackedPosition;
private:

	PLAYER_TYPE m_playerMesh;
	PLAYER_AMMO_TYPE m_weaponChoice;
	PLAYER_CURRENT_STATE m_playerState;
	ALERT_STATE m_AlertState;

	static CCharacter_Player* mInstance;

	//for sound
	CSoundManager Sound;
	int walkLimit;
	float m_DetectionLevel;
	bool m_HasBeenDetected;
	float m_DetectionFadeTimer;
	bool DetectionFading;
};

