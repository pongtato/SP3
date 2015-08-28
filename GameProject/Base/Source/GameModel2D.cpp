#include "GameModel2D.h"

#include "MeshBuilder.h"
#include "LoadTGA.h"
#include "SpriteAnimation.h"

#include "Character_Enemy.h"
#include "Weapon.h"

const float m_worldHeight = 120;
const float m_worldWidth = 160;

void GameModel2D::Init()
{
	Model::Init();
	camera.Init(Vector3(20, 15, 50), Vector3(20, 15, 0), Vector3(0, 1, 0));
	for (int count = 0; count < GEOMETRY_TYPE::TOTAL_GEOMETRY; ++count)
	{
		meshList[count] = new Mesh("null");
		meshList[count]->textureID[0] = 0;
	}
	meshList[TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[TEXT]->textureID[0] = LoadTGA("Image//calibri.tga");
	meshList[BACKGROUND] = MeshBuilder::GenerateQuad("background", Color());
	meshList[BACKGROUND]->textureID[0] = LoadTGA("Image\\background.tga");
	meshList[TILE] = MeshBuilder::GenerateText("tile", 12, 5);
	meshList[TILE]->textureID[0] = LoadTGA("Image\\Maps\\World.tga");
	meshList[TILEFLOOR] = MeshBuilder::GenerateText("tile", 12, 5);
	meshList[TILEFLOOR]->textureID[0] = LoadTGA("Image\\Maps\\World.tga");
	meshList[PLAYER] = MeshBuilder::GenerateText("player", 8, 16);
	meshList[PLAYER]->textureID[0] = LoadTGA("Image//Player.tga");
	meshList[MOBS] = MeshBuilder::GenerateText("mobs", 4, 4);
	meshList[MOBS]->textureID[0] = LoadTGA("Image//mobs.tga");
	meshList[CROSSHAIR] = MeshBuilder::GenerateQuad("Crosshair", Color());
	meshList[CROSSHAIR]->textureID[0] = LoadTGA("Image\\Crosshair.tga");
	meshList[BULLET] = MeshBuilder::GenerateSphere("Bullet", Color(1, 0, 0),10,10,1.0f);
	meshList[EBULLET] = MeshBuilder::GenerateSphere("EnemyBullet", Color(0, 0, 1), 10, 10, 1.0f);
	meshList[CUBE] = MeshBuilder::GenerateCube("Bullet", Color(1, 0, 0),1.0f);
	meshList[FOG] = MeshBuilder::GenerateSpriteAnimation("FOG", 1, 1);
	meshList[FOG]->textureID[0] = LoadTGA("Image\\FOG.tga");

	//Player
	meshList[PISTOL_IDLE] = MeshBuilder::GenerateSpriteAnimation("PISTOL_IDLE", 4, 5);
	meshList[PISTOL_IDLE]->textureID[0] = LoadTGA("Image\\Player\\PISTOL_IDLE.tga");
	meshList[PISTOL_RELOAD] = MeshBuilder::GenerateSpriteAnimation("PISTOL_RELOAD", 4, 4);
	meshList[PISTOL_RELOAD]->textureID[0] = LoadTGA("Image\\Player\\PISTOL_RELOAD.tga");
	meshList[PISTOL_SHOOT] = MeshBuilder::GenerateSpriteAnimation("PISTOL_SHOOT", 2, 2);
	meshList[PISTOL_SHOOT]->textureID[0] = LoadTGA("Image\\Player\\PISTOL_SHOOT.tga");

	meshList[RIFLE_IDLE] = MeshBuilder::GenerateSpriteAnimation("RIFLE_IDLE", 5, 4);
	meshList[RIFLE_IDLE]->textureID[0] = LoadTGA("Image\\Player\\RIFLE_IDLE.tga");
	meshList[RIFLE_RELOAD] = MeshBuilder::GenerateSpriteAnimation("RIFLE_RELOAD", 5, 4);
	meshList[RIFLE_RELOAD]->textureID[0] = LoadTGA("Image\\Player\\RIFLE_RELOAD.tga");
	meshList[RIFLE_SHOOT] = MeshBuilder::GenerateSpriteAnimation("RIFLE_SHOOT", 2, 2);
	meshList[RIFLE_SHOOT]->textureID[0] = LoadTGA("Image\\Player\\RIFLE_SHOOT.tga");

	meshList[SHOTGUN_IDLE] = MeshBuilder::GenerateSpriteAnimation("SHOTGUN_IDLE", 5, 4);
	meshList[SHOTGUN_IDLE]->textureID[0] = LoadTGA("Image\\Player\\SHOTGUN_IDLE.tga");
	meshList[SHOTGUN_RELOAD] = MeshBuilder::GenerateSpriteAnimation("SHOTGUN_RELOAD", 5, 4);
	meshList[SHOTGUN_RELOAD]->textureID[0] = LoadTGA("Image\\Player\\SHOTGUN_RELOAD.tga");
	meshList[SHOTGUN_SHOOT] = MeshBuilder::GenerateSpriteAnimation("SHOTGUN_SHOOT", 2, 2);
	meshList[SHOTGUN_SHOOT]->textureID[0] = LoadTGA("Image\\Player\\SHOTGUN_SHOOT.tga");

	//Enemy
	meshList[ENEMY_LIGHT_IDLE] = MeshBuilder::GenerateSpriteAnimation("ENEMY_IDLE", 1, 20);
	meshList[ENEMY_LIGHT_IDLE]->textureID[0] = LoadTGA("Image\\Enemy\\ENEMY_IDLE.tga");

	meshList[ENEMY_CAMERA] = MeshBuilder::GenerateSpriteAnimation("ENEMY_CAMERA", 1, 1);
	meshList[ENEMY_CAMERA]->textureID[0] = LoadTGA("Image\\Enemy\\ENEMY_CAMERA.tga");

	meshList[ALERT] = MeshBuilder::GenerateSpriteAnimation("ALERT", 1, 1);
	meshList[ALERT]->textureID[0] = LoadTGA("Image\\Enemy\\ALERT.tga");

	meshList[CAUTION] = MeshBuilder::GenerateSpriteAnimation("CAUTION", 1, 1);
	meshList[CAUTION]->textureID[0] = LoadTGA("Image\\Enemy\\CAUTION.tga");
	//Text Prompts
	meshList[TEXT_PROMPT] = MeshBuilder::GenerateQuad("TEXT_PROMPT", 1, 20);
	meshList[TEXT_PROMPT]->textureID[0] = LoadTGA("Image\\DialogueBoxTemp.tga");

	//UI - Health
	meshList[HEALTH] = MeshBuilder::GenerateQuad("HEALTH", 1, 20);
	meshList[HEALTH]->textureID[0] = LoadTGA("Image\\HealthBar.tga");

	//UI - Health Bar
	meshList[HEALTH_BAR] = MeshBuilder::GenerateQuad("HEALTH_BAR", 0, 20);

	//Weapon Icon
	meshList[PISTOL_ICON] = MeshBuilder::GenerateQuad("PISTOL_ICON", 1, 20);
	meshList[PISTOL_ICON]->textureID[0] = LoadTGA("Image\\IconPistol.tga");

	meshList[RIFLE_ICON] = MeshBuilder::GenerateQuad("RIFLE_ICON", 1, 20);
	meshList[RIFLE_ICON]->textureID[0] = LoadTGA("Image\\IconRifle.tga");

	meshList[SHOTGUN_ICON] = MeshBuilder::GenerateQuad("SHOTGUN_ICON", 1, 20);
	meshList[SHOTGUN_ICON]->textureID[0] = LoadTGA("Image\\IconShotgun.tga");

	//Weapon Ammo
	meshList[PISTOL_AMMO] = MeshBuilder::GenerateQuad("PISTOL_AMMO", 1, 20);
	meshList[PISTOL_AMMO]->textureID[0] = LoadTGA("Image\\PistolBullet.tga");

	meshList[RIFLE_AMMO] = MeshBuilder::GenerateQuad("RIFLE_AMMO", 1, 20);
	meshList[RIFLE_AMMO]->textureID[0] = LoadTGA("Image\\RifleBullet.tga");

	meshList[SHOTGUN_AMMO] = MeshBuilder::GenerateQuad("SHOTGUN_AMMO", 1, 20);
	meshList[SHOTGUN_AMMO]->textureID[0] = LoadTGA("Image\\ShotgunShell.tga");

	//Lock picking
	meshList[LOCKPICKBG] = MeshBuilder::GenerateQuad("LPBG", 0, 1.0f);
	meshList[LOCKPICKBG]->textureID[0] = LoadTGA("Image\\LockPickBG.tga");

	meshList[LOCKPICKBAR] = MeshBuilder::GenerateQuad("LPBAR", Color(0, 0, 1), 1.0f);

	meshList[LOCKPICKBALL] = MeshBuilder::GenerateSphere("LPBALL", Color(1, 0, 0), 20, 20, 1.0f);


	//Animation Init
	SpriteAnimation *eENEMY_LIGHT_IDLE = dynamic_cast<SpriteAnimation*>(meshList[ENEMY_LIGHT_IDLE]);
	if(eENEMY_LIGHT_IDLE)
	{
		eENEMY_LIGHT_IDLE->m_anim = new Animation();
		//Start frame, end frame, repeat, time
		eENEMY_LIGHT_IDLE->m_anim->Set(0, 19, 0, 2.0f);
	} 

	SpriteAnimation *ePISTOL_IDLE = dynamic_cast<SpriteAnimation*>(meshList[PISTOL_IDLE]);
	if(ePISTOL_IDLE)
	{
		ePISTOL_IDLE->m_anim = new Animation();
		//Start frame, end frame, repeat, time
		ePISTOL_IDLE->m_anim->Set(0, 19, 0, 2.0f);
	} 

	SpriteAnimation *ePISTOL_RELOAD = dynamic_cast<SpriteAnimation*>(meshList[PISTOL_RELOAD]);
	if(ePISTOL_RELOAD)
	{
		ePISTOL_RELOAD->m_anim = new Animation();
		//Start frame, end frame, repeat, time
		ePISTOL_RELOAD->m_anim->Set(0, 14, 0, 2.0f);
	} 

	SpriteAnimation *ePISTOL_SHOOT = dynamic_cast<SpriteAnimation*>(meshList[PISTOL_SHOOT]);
	if(ePISTOL_SHOOT)
	{
		ePISTOL_SHOOT->m_anim = new Animation();
		//Start frame, end frame, repeat, time
		ePISTOL_SHOOT->m_anim->Set(0, 2, 0, 2.0f);
	} 

	SpriteAnimation *eRIFLE_IDLE = dynamic_cast<SpriteAnimation*>(meshList[RIFLE_IDLE]);
	if(eRIFLE_IDLE)
	{
		eRIFLE_IDLE->m_anim = new Animation();
		//Start frame, end frame, repeat, time
		eRIFLE_IDLE->m_anim->Set(0, 19, 0, 2.0f);
	} 

	SpriteAnimation *eRIFLE_RELOAD = dynamic_cast<SpriteAnimation*>(meshList[RIFLE_RELOAD]);
	if(eRIFLE_RELOAD)
	{
		eRIFLE_RELOAD->m_anim = new Animation();
		//Start frame, end frame, repeat, time
		eRIFLE_RELOAD->m_anim->Set(0, 19, 0, 2.0f);
	} 

	SpriteAnimation *eRIFLE_SHOOT = dynamic_cast<SpriteAnimation*>(meshList[RIFLE_SHOOT]);
	if(eRIFLE_SHOOT)
	{
		eRIFLE_SHOOT->m_anim = new Animation();
		//Start frame, end frame, repeat, time
		eRIFLE_SHOOT->m_anim->Set(0, 2, 0, 2.0f);
	} 

	SpriteAnimation *eSHOTGUN_IDLE = dynamic_cast<SpriteAnimation*>(meshList[SHOTGUN_IDLE]);
	if(eSHOTGUN_IDLE)
	{
		eSHOTGUN_IDLE->m_anim = new Animation();
		//Start frame, end frame, repeat, time
		eSHOTGUN_IDLE->m_anim->Set(0, 19, 0, 2.0f);
	} 

	SpriteAnimation *eHOTGUN_RELOAD = dynamic_cast<SpriteAnimation*>(meshList[SHOTGUN_RELOAD]);
	if(eHOTGUN_RELOAD)
	{
		eHOTGUN_RELOAD->m_anim = new Animation();
		//Start frame, end frame, repeat, time
		eHOTGUN_RELOAD->m_anim->Set(0, 19, 0, 2.0f);
	} 

	SpriteAnimation *eSHOTGUN_SHOOT = dynamic_cast<SpriteAnimation*>(meshList[SHOTGUN_SHOOT]);
	if(eSHOTGUN_SHOOT)
	{
		eSHOTGUN_SHOOT->m_anim = new Animation();
		//Start frame, end frame, repeat, time
		eSHOTGUN_SHOOT->m_anim->Set(0, 2, 0, 2.0f);
	} 

	commands = new bool[NUM_COMMANDS];
	for (int count = 0; count < NUM_COMMANDS; ++count)
		commands[count] = false;

	//m_mapOffset_x = 0;
	//m_mapOffset_y = 0;
	
	newPlayerPos.Set(0,0,0);
	newExitPos.Set(0,0,0);
	score = 0;
	CDTimer = 60;
	CDTimerLimit = 0;
	ZoomIN = false;
	SpawnReady = false;
	newLevel = false;
	//BulletShoot = false;
	hasReadLoc = false;
	AniToUpdate = PISTOL_IDLE;
	srand (time(NULL));
	GroupToSpawn = rand() % 3 + 0;
	m_EnemySpawnCount = 0;

	WeaponChangeCooldown = 0.5f;

	KEYCOUNT = 0;
	LaserActive = true;
	InLockPick1 = false;
	InLockPick2 = false;
	LockPickY = 0;
	LockPickUp = true;
	LockPickBoxTop = 1;
	LockPickBoxBtm = -1;

	for ( unsigned i = 0; i < 1000; ++i)
	{
		GameObject * go = new GameObject(GameObject::GO_NONE);
		m_goList.push_back(go);
		GameObject * fog = new GameObject(GameObject::GO_NONE);
		m_fogList.push_back(fog);
		GameObject * fogcheck = new GameObject(GameObject::GO_NONE);
		m_fogCheckerList.push_back(fogcheck);
	}
	for ( unsigned i = 0; i < 100; ++i)
	{
		GameObject * collectibles = new GameObject(GameObject::GO_NONE);
		CollectiblesList.push_back(collectibles);
		GameObject * interact = new GameObject(GameObject::GO_NONE);
		InteractionList.push_back(interact);
		GameObject * checker = new GameObject(GameObject::GO_NONE);
		m_checkingList.push_back(checker);
		CCharacter_Enemy * enemy = new CCharacter_Enemy();
		EnemyList.push_back(enemy);
	}
}

void GameModel2D::VeryRealRaycasting(double dt)
{
	//Tick for reudcing alert level
	CCharacter_Player::GetInstance()->ManipulateDetectionFadeTimer(-float(dt));

	if ( CCharacter_Player::GetInstance()->getDetectionFadeTimer() <= 0 )
	{
		CCharacter_Player::GetInstance()->ManipulateDetectionLevel(-float(dt));
	}

	for (std::vector<CCharacter_Enemy *>::iterator it = EnemyList.begin(); it != EnemyList.end(); ++it)
	{
		CCharacter_Enemy *go = (CCharacter_Enemy *)*it;
		if ( go->getActive() )
		{
			if ( go->detectPlayer(CCharacter_Player::GetInstance()->getPosition(),getTileMap()) )
			{
				for (std::vector<GameObject *>::iterator it = m_checkingList.begin(); it != m_checkingList.end(); ++it)
				{
					//Spawn checker
					GameObject *checker = (GameObject *)*it;
					if (!checker->active)
					{
						checker->type = GameObject::GO_EBULLET;
						checker->active = true;
						checker->scale.Set(0.05, 0.05, 0.05);
						checker->pos = go->getPosition();
						checker->vel = go->LineOfSight;
						checker->ID = go->getGroupID();
						break;
					}
				}
			}
			for (std::vector<GameObject *>::iterator it = m_checkingList.begin(); it != m_checkingList.end(); ++it)
			{
				GameObject *checker = (GameObject *)*it;
				if (checker->active)
				{
					checker->pos += checker->vel * (float)dt;
					if ( (CCharacter_Player::GetInstance()->getPosition() - checker->pos).Length() < 1.f )
					{
						//collide with player = true
						if ( checker->ID == go->getGroupID() && CCharacter_Player::GetInstance()->getAlertState() == CCharacter_Player::GetInstance()->UNDETECTED)
						{
							go->InLineOfSight = true;
							go->setTargetPosition(CCharacter_Player::GetInstance()->getPosition());
							go->setNewState(go->TRACKING);
							//Player detected reset fading time
							CCharacter_Player::GetInstance()->ResetTimer();
							//Increase alert level
							CCharacter_Player::GetInstance()->ManipulateDetectionLevel(float(dt));
							checker->active = false;
						}
					}
					float tempX = checker->pos.x + 0.5f;
					float tempY = checker->pos.y + 0.5f;
					if (getTileMap()->getTile(tempX, floor(tempY)) >= 0 && getTileMap()->getTile(tempX, floor(tempY)) <= 15 )
					{
						if ( checker->ID == go->getGroupID() )
						{
							//Collided with wall, obstacle in the way
							//go->setVelocity(0,0,0);
							if ( go->InLineOfSight )
							{
								go->resetTimer();
								//go->setNewState(go->SCANNING);
								if ( go->getAmmoType() != go->CAMERA )
								{
									go->setRotateDirection(go->getTargetPosition());
								}
								go->InLineOfSight = false;
							}
							checker->active = false;
						}
					}
				}
			}
		}
	}
}

void GameModel2D::Update(double dt)
{
	float fps = (1 / dt);
	//countdown timer
	CDTimerLimit += 1;

	if (CDTimerLimit > fps)
	{
		CDTimerLimit = 0;
		CDTimer -= 1;
	}
	//allow gameplay after zoom in
	if (ZoomIN)
	{
		if (commands[MOVE_UP]) CCharacter_Player::GetInstance()->moveUp();
		if (commands[MOVE_DOWN]) CCharacter_Player::GetInstance()->moveDown();
		if (commands[MOVE_LEFT]) CCharacter_Player::GetInstance()->moveLeft();
		if (commands[MOVE_RIGHT]) CCharacter_Player::GetInstance()->moveRight();
	}
	if (!InLockPick1 || !InLockPick2)
	{
		CCharacter_Player::GetInstance()->Update(dt, getTileMap());
	}
	//Weapon changing
	int CurrentWeapon = CCharacter_Player::GetInstance()->getAmmoType();
	if (commands[PREVWEAP] && WeaponChangeCooldown < 0)
	{
		CurrentWeapon--;
		WeaponChangeCooldown = 0.5f;
	}
	if (commands[NEXTWEAP] && WeaponChangeCooldown < 0)
	{
		CurrentWeapon++;
		WeaponChangeCooldown = 0.5f;
	}
	WeaponChangeCooldown -= dt;

	CCharacter_Player::GetInstance()->setAmmoType(CurrentWeapon);

	//Weapons firecooldown
	CPistol::GetInstance()->FireCooldownTick(dt);
	CShotgun::GetInstance()->FireCooldownTick(dt);
	CRifle::GetInstance()->FireCooldownTick(dt);
	EPistol::GetInstance()->FireCooldownTick(dt);

	//Shooting (Bullet spawning)
	if (commands[SHOOT])
	{
		switch (CCharacter_Player::GetInstance()->getAmmoType())
		{
		case 0:
			if (CPistol::GetInstance()->GetAmmo() > 0 && CPistol::GetInstance()->GetFireCooldown() <= 0.0f)
			{
				//Pistol fire sound
				Sound.pistolShot();
				//Spawn Bullet
				SpawnBullet(CPistol::GetInstance()->GetDamage(), 0.5f);
				//Ammo decrease
				CPistol::GetInstance()->UseAmmo(1);
				CPistol::GetInstance()->ResetCooldown();
			}
			else if (CPistol::GetInstance()->GetAmmo() < 1 && CPistol::GetInstance()->GetFireCooldown() <= 0.0f)
			{
				Sound.emptyClip();
				CPistol::GetInstance()->ResetCooldown();
			}
			break;
		case 1:
			if (CRifle::GetInstance()->GetAmmo() > 0 && CRifle::GetInstance()->GetFireCooldown() <= 0.0f)
			{
				//rifle fire sound
				Sound.rifleShot();
				//Spawn Bullet
				SpawnBullet(CRifle::GetInstance()->GetDamage(), 1.2f);
				//Ammo decrease
				CRifle::GetInstance()->UseAmmo(1);
				CRifle::GetInstance()->ResetCooldown();
			}
			else if (CRifle::GetInstance()->GetAmmo() < 1 && CRifle::GetInstance()->GetFireCooldown() <= 0.0f)
			{
				Sound.emptyClip();
				CRifle::GetInstance()->ResetCooldown();
			}
			break;
		case 2:
			if (CShotgun::GetInstance()->GetAmmo() > 0 && CShotgun::GetInstance()->GetFireCooldown() <= 0.0f)
			{
				//Shotgun fire sound
				Sound.shotgunShot();
				//Spawn Bullet
				for (int i = 0; i < 7; i++)
				{
					SpawnSGBullets(CShotgun::GetInstance()->GetDamage(), 1.0f);
				}
				//Ammo decrease
				CShotgun::GetInstance()->UseAmmo(7);
				CShotgun::GetInstance()->ResetCooldown();

			}
			else if (CShotgun::GetInstance()->GetAmmo() < 1 && CShotgun::GetInstance()->GetFireCooldown() <= 0.0f)
			{
				Sound.emptyClip();
				CShotgun::GetInstance()->ResetCooldown();
			}
			break;
		}
	}
	else if (!commands[SHOOT])
	{
	}

	//Reload
	if (commands[RELOAD])
	{

		switch (CCharacter_Player::GetInstance()->getAmmoType())
		{
		case 0:
			if (CPistol::GetInstance()->GetAmmo() == 0)
			{
				Sound.reloadSound();
				CPistol::GetInstance()->SetAmmo(10);
			}
			break;
		case 1:
			if (CRifle::GetInstance()->GetAmmo() == 0)
			{
				Sound.reloadSound();
				CRifle::GetInstance()->SetAmmo(50);
			}

			break;
		case 2:
			if (CShotgun::GetInstance()->GetAmmo() == 0)
			{
				Sound.reloadSound();
				CShotgun::GetInstance()->SetAmmo(70);
			}
			break;
		}
	}

	for (int i = 0; i < CollectiblesList.size(); i++)
	{
		if (CollectiblesList[i]->type == GameObject::GO_KEY_ID && CollectiblesList[i]->active)
		{
			if((CollectiblesList[i]->pos - CCharacter_Player::GetInstance()->getPosition()).Length() < 1)
			{
				CollectiblesList[i]->active = false;
				KEYCOUNT++;
				break;
			}
		}
	}


	//Lock Key Collision Collection
	for (int i = 0; i < InteractionList.size(); i++)
	{
		if (InteractionList[i]->type == GameObject::GO_LOCK_KEY_ID && InteractionList[i]->active)
		{
			//Lock collision
			Vector3 position = CCharacter_Player::GetInstance()->getPosition();
			Vector3 velocity = CCharacter_Player::GetInstance()->getVelocity();
			position.x += velocity.x * dt;
			if (velocity.x < 0)
				position.x = floor(position.x);
			else if (velocity.x > 0)
				position.x = ceil(position.x);
			if (getTileMap()->getTile(position.x, floor(position.y)) == KEYUNLOCK_ID && getTileMap()->getTile(position.x, floor(position.y)) == KEYUNLOCK_ID &&
				(InteractionList[i]->pos - CCharacter_Player::GetInstance()->getPosition()).Length() < 1.5f || 
				getTileMap()->getTile(position.x, ceil(position.y)) == KEYUNLOCK_ID && getTileMap()->getTile(position.x, ceil(position.y)) == KEYUNLOCK_ID &&
				(InteractionList[i]->pos - CCharacter_Player::GetInstance()->getPosition()).Length() < 1.5f)
			{
				CCharacter_Player::GetInstance()->setPosition(position.x + (velocity.x < -0.0f ? 1 : -1), position.y, position.z);
				velocity.x = 0;
			}
			position = CCharacter_Player::GetInstance()->getPosition();
			position.y += velocity.y * dt;
			if (velocity.y < 0)
				position.y = floor(position.y);
			else if (velocity.y > 0)
				position.y = ceil(position.y);
			if (getTileMap()->getTile(floor(position.x), position.y) == KEYUNLOCK_ID && getTileMap()->getTile(floor(position.x), position.y) == KEYUNLOCK_ID &&
				(InteractionList[i]->pos - CCharacter_Player::GetInstance()->getPosition()).Length() < 1.5f || 
				getTileMap()->getTile(ceil(position.x), position.y) == KEYUNLOCK_ID && getTileMap()->getTile(ceil(position.x), position.y) == KEYUNLOCK_ID &&
				(InteractionList[i]->pos - CCharacter_Player::GetInstance()->getPosition()).Length() < 1.5f)
			{
				CCharacter_Player::GetInstance()->setPosition(position.x, position.y + (velocity.y < -0.0f ? 1 : -1), position.z);
				velocity.y = 0;
			}
			position += velocity * dt;
			if ((InteractionList[i]->pos - CCharacter_Player::GetInstance()->getPosition()).Length() < 1.5f && KEYCOUNT > 0)
			{
				InteractionList[i]->active = false;
				KEYCOUNT--;
				break;
			}
		}

		if (InteractionList[i]->type == GameObject::GO_EXIT && InteractionList[i]->active)
		{

			//Lock collision
			Vector3 position = CCharacter_Player::GetInstance()->getPosition();
			Vector3 velocity = CCharacter_Player::GetInstance()->getVelocity();
			position.x += velocity.x * dt;
			if (velocity.x < 0)
				position.x = floor(position.x);
			else if (velocity.x > 0)
				position.x = ceil(position.x);
			if (getTileMap()->getTile(position.x, floor(position.y)) == EXIT_ID && getTileMap()->getTile(position.x, floor(position.y)) == EXIT_ID &&
				(InteractionList[i]->pos - CCharacter_Player::GetInstance()->getPosition()).Length() < 1.5f || 
				getTileMap()->getTile(position.x, ceil(position.y)) == EXIT_ID && getTileMap()->getTile(position.x, ceil(position.y)) == EXIT_ID &&
				(InteractionList[i]->pos - CCharacter_Player::GetInstance()->getPosition()).Length() < 1.5f)
			{
				switch ( m_CurrentLevel)
				{
				case 1:
					Sound.engine->stopAllSounds();
					m_CurrentLevel = 2;
					throw m_CurrentLevel - 1;
					break;
				case 2:
					Sound.engine->stopAllSounds();
					m_CurrentLevel = 3;
					throw m_CurrentLevel - 1;
					break;
				case 3:
					Sound.engine->stopAllSounds();
					m_CurrentLevel = 4;
					throw m_CurrentLevel - 1;
					break;
				}
				break;
			}
			position = CCharacter_Player::GetInstance()->getPosition();
			position.y += velocity.y * dt;
			if (velocity.y < 0)
				position.y = floor(position.y);
			else if (velocity.y > 0)
				position.y = ceil(position.y);
			if (getTileMap()->getTile(floor(position.x), position.y) == EXIT_ID && getTileMap()->getTile(floor(position.x), position.y) == EXIT_ID &&
				(InteractionList[i]->pos - CCharacter_Player::GetInstance()->getPosition()).Length() < 1.5f || 
				getTileMap()->getTile(ceil(position.x), position.y) == EXIT_ID && getTileMap()->getTile(ceil(position.x), position.y) == EXIT_ID &&
				(InteractionList[i]->pos - CCharacter_Player::GetInstance()->getPosition()).Length() < 1.5f)
			{
				CCharacter_Player::GetInstance()->setPosition(position.x, position.y + (velocity.y < -0.0f ? 1 : -1), position.z);
				velocity.y = 0;
			}
			position += velocity * dt;
			if ((InteractionList[i]->pos - CCharacter_Player::GetInstance()->getPosition()).Length() < 1.5f && KEYCOUNT > 0)
			{
				switch ( m_CurrentLevel)
				{
				case 1:
					m_CurrentLevel = 2;
					throw m_CurrentLevel - 1;
					break;
				case 2:
					m_CurrentLevel = 3;
					throw m_CurrentLevel - 1;
					break;
				case 3:
					m_CurrentLevel = 4;
					throw m_CurrentLevel - 1;
					break;
				}
				break;
			}
		}
	}

	//Computer Laser Collision Activation
	for (int i = 0; i < InteractionList.size(); i++)
	{
		if (InteractionList[i]->type == GameObject::GO_PC && InteractionList[i]->active)
		{
			//PC collision
			Vector3 position = CCharacter_Player::GetInstance()->getPosition();
			Vector3 velocity = CCharacter_Player::GetInstance()->getVelocity();
			position.x += velocity.x * dt;
			if (velocity.x < 0)
				position.x = floor(position.x);
			else if (velocity.x > 0)
				position.x = ceil(position.x);
			if (getTileMap()->getTile(position.x, floor(position.y)) == 39 && getTileMap()->getTile(position.x, floor(position.y)) == 39 &&
				(InteractionList[i]->pos - CCharacter_Player::GetInstance()->getPosition()).Length() < 1.5f ||
				getTileMap()->getTile(position.x, ceil(position.y)) == 39 && getTileMap()->getTile(position.x, ceil(position.y)) == 39 &&
				(InteractionList[i]->pos - CCharacter_Player::GetInstance()->getPosition()).Length() < 1.5f)
			{
				CCharacter_Player::GetInstance()->setPosition(position.x + (velocity.x < -0.0f ? 1 : -1), position.y, position.z);
				velocity.x = 0;
			}
			position = CCharacter_Player::GetInstance()->getPosition();
			position.y += velocity.y * dt;
			if (velocity.y < 0)
				position.y = floor(position.y);
			else if (velocity.y > 0)
				position.y = ceil(position.y);
			if (getTileMap()->getTile(floor(position.x), position.y) == 39 && getTileMap()->getTile(floor(position.x), position.y) == 39 &&
				(InteractionList[i]->pos - CCharacter_Player::GetInstance()->getPosition()).Length() < 1.5f ||
				getTileMap()->getTile(ceil(position.x), position.y) == 39 && getTileMap()->getTile(ceil(position.x), position.y) == 39 &&
				(InteractionList[i]->pos - CCharacter_Player::GetInstance()->getPosition()).Length() < 1.5f)
			{
				CCharacter_Player::GetInstance()->setPosition(position.x, position.y + (velocity.y < -0.0f ? 1 : -1), position.z);
				velocity.y = 0;
			}
			position += velocity * dt;
			if ((InteractionList[i]->pos - CCharacter_Player::GetInstance()->getPosition()).Length() < 1.5f && LaserActive)
			{
				Sound.PCON();
				LaserActive = false;
				break;
			}
		}
	}
	//Laser Deactivation
	for (int i = 0; i < CollectiblesList.size(); i++)
	{
		if ((CollectiblesList[i]->type == GameObject::GO_LASER_HORI || CollectiblesList[i]->type == GameObject::GO_LASER_VERTI) && CollectiblesList[i]->active)
		{
			if (!LaserActive)
			{
				CollectiblesList[i]->active = false;
			}
		}
	}

	//LockPicking
	for (int i = 0; i < InteractionList.size(); i++)
	{
		if (InteractionList[i]->type == GameObject::GO_LOCKPICK_1 && InteractionList[i]->active)
		{
			//Lock collision
			Vector3 position = CCharacter_Player::GetInstance()->getPosition();
			Vector3 velocity = CCharacter_Player::GetInstance()->getVelocity();
			position.x += velocity.x * dt;
			if (velocity.x < 0)
				position.x = floor(position.x);
			else if (velocity.x > 0)
				position.x = ceil(position.x);
			if (getTileMap()->getTile(position.x, floor(position.y)) >= 41 && getTileMap()->getTile(position.x, floor(position.y)) <= 42 &&
				(InteractionList[i]->pos - CCharacter_Player::GetInstance()->getPosition()).Length() < 1.5f ||
				getTileMap()->getTile(position.x, ceil(position.y)) >= 41 && getTileMap()->getTile(position.x, ceil(position.y)) <= 42 &&
				(InteractionList[i]->pos - CCharacter_Player::GetInstance()->getPosition()).Length() < 1.5f)
			{
				CCharacter_Player::GetInstance()->setPosition(position.x + (velocity.x < -0.0f ? 1 : -1), position.y, position.z);
				velocity.x = 0;
				if (commands[INTERACT])
				{
					InLockPick1 = true;
				}
			}
			position = CCharacter_Player::GetInstance()->getPosition();
			position.y += velocity.y * dt;
			if (velocity.y < 0)
				position.y = floor(position.y);
			else if (velocity.y > 0)
				position.y = ceil(position.y);
			if (getTileMap()->getTile(floor(position.x), position.y) >= 41 && getTileMap()->getTile(floor(position.x), position.y) <= 42 &&
				(InteractionList[i]->pos - CCharacter_Player::GetInstance()->getPosition()).Length() < 1.5f ||
				getTileMap()->getTile(ceil(position.x), position.y) >= 41 && getTileMap()->getTile(ceil(position.x), position.y) <= 42 &&
				(InteractionList[i]->pos - CCharacter_Player::GetInstance()->getPosition()).Length() < 1.5f)
			{
				CCharacter_Player::GetInstance()->setPosition(position.x, position.y + (velocity.y < -0.0f ? 1 : -1), position.z);
				velocity.y = 0;
				if (commands[INTERACT])
				{
					InLockPick1 = true;
				}
			}
			position += velocity * dt;
		}

		if (InteractionList[i]->type == GameObject::GO_LOCKPICK_2 && InteractionList[i]->active)
		{
			//Lock collision
			Vector3 position = CCharacter_Player::GetInstance()->getPosition();
			Vector3 velocity = CCharacter_Player::GetInstance()->getVelocity();
			position.x += velocity.x * dt;
			if (velocity.x < 0)
				position.x = floor(position.x);
			else if (velocity.x > 0)
				position.x = ceil(position.x);
			if (getTileMap()->getTile(position.x, floor(position.y)) >= 41 && getTileMap()->getTile(position.x, floor(position.y)) <= 42 &&
				(InteractionList[i]->pos - CCharacter_Player::GetInstance()->getPosition()).Length() < 1.5f ||
				getTileMap()->getTile(position.x, ceil(position.y)) >= 41 && getTileMap()->getTile(position.x, ceil(position.y)) <= 42 &&
				(InteractionList[i]->pos - CCharacter_Player::GetInstance()->getPosition()).Length() < 1.5f)
			{
				CCharacter_Player::GetInstance()->setPosition(position.x + (velocity.x < -0.0f ? 1 : -1), position.y, position.z);
					InLockPick2 = true;
				if (commands[INTERACT])
				{
					InLockPick2 = true;
				}
			}
			position = CCharacter_Player::GetInstance()->getPosition();
			position.y += velocity.y * dt;
			if (velocity.y < 0)
				position.y = floor(position.y);
			else if (velocity.y > 0)
				position.y = ceil(position.y);
			if (getTileMap()->getTile(floor(position.x), position.y) >= 41 && getTileMap()->getTile(floor(position.x), position.y) <= 42 &&
				(InteractionList[i]->pos - CCharacter_Player::GetInstance()->getPosition()).Length() < 1.5f ||
				getTileMap()->getTile(ceil(position.x), position.y) >= 41 && getTileMap()->getTile(ceil(position.x), position.y) <= 42 &&
				(InteractionList[i]->pos - CCharacter_Player::GetInstance()->getPosition()).Length() < 1.5f)
			{
				CCharacter_Player::GetInstance()->setPosition(position.x, position.y + (velocity.y < -0.0f ? 1 : -1), position.z);
				velocity.y = 0;
				if (commands[INTERACT])
				{
					InLockPick2 = true;
				}
			}
			position += velocity * dt;
		}
	}

	if (LockPickUp)
	{
		LockPickY += static_cast<float>(dt * 10);
		if (LockPickY > 12)
		{
			LockPickUp = false;
		}
	}
	else if (!LockPickUp)
	{
		LockPickY -= static_cast<float>(dt * 10);
		if (LockPickY < -12)
		{
			LockPickUp = true;
		}
	}
	if (commands[UNLOCK] && InLockPick1 == true)
	{
		if (LockPickY <= LockPickBoxTop && LockPickY >= LockPickBoxBtm)
		{
			InLockPick1 = false;
			for (int i = 0; i < InteractionList.size(); i++)
			{
				if (InteractionList[i]->type == GameObject::GO_LOCKPICK_1)
				{
					InteractionList[i]->active = false;
				}
			}
		}
		else if (LockPickY > LockPickBoxTop || LockPickY < LockPickBoxBtm)
		{
			InLockPick1= false;
		}
	}
	if (commands[UNLOCK] && InLockPick2 == true)
	{
		if (LockPickY <= LockPickBoxTop && LockPickY >= LockPickBoxBtm)
		{
			InLockPick2 = false;
			for (int i = 0; i < InteractionList.size(); i++)
			{
				if (InteractionList[i]->type == GameObject::GO_LOCKPICK_2)
				{
					InteractionList[i]->active = false;
				}
			}
		}
		else if (LockPickY > LockPickBoxTop || LockPickY < LockPickBoxBtm)
		{
			InLockPick2 = false;
		}
	}

	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go->active && go->type == GameObject::GO_BULLET) //Player Bullet
		{
			for (unsigned i = 0; i < EnemyList.size(); ++i)
			{
				if (EnemyList[i]->getActive())
				{
					if (go->pos.x < EnemyList[i]->getPosition().x + 0.5f && go->pos.x > EnemyList[i]->getPosition().x - 0.5f && go->pos.y < EnemyList[i]->getPosition().y + 0.5f && go->pos.y > EnemyList[i]->getPosition().y - 0.5f)
					{
						go->active = false;
						EnemyList[i]->setActive(false);
					}
				}

			}
		}
		if (go->active && go->type == GameObject::GO_EBULLET) //Enemy Bullet
		{
			for (unsigned i = 0; i < EnemyList.size(); ++i)
			{
				if (EnemyList[i]->getActive())
				{
					float tempX = go->pos.x + 0.5f;
					float tempY = go->pos.y + 0.5f;


					if (getTileMap()->getTile(tempX, floor(tempY)) >= 0 && getTileMap()->getTile(tempX, floor(tempY)) <= 15 )
					{
						go->active = false;
					}
				}

			}
			if (go->pos.x < CCharacter_Player::GetInstance()->getPosition().x + 0.5f && go->pos.x > CCharacter_Player::GetInstance()->getPosition().x - 0.5f && go->pos.y <CCharacter_Player::GetInstance()->getPosition().y + 0.5f && go->pos.y > CCharacter_Player::GetInstance()->getPosition().y - 0.5f)
			{
				go->active = false;
				CCharacter_Player::GetInstance()->Damaged(25);
			}
		}

		if (go->active && (go->type == GameObject::GO_BULLET || go->type == GameObject::GO_EBULLET))
		{

			float tempX = go->pos.x + 0.5f;
			float tempY = go->pos.y + 0.5f;


			if (getTileMap()->getTile(tempX, floor(tempY)) >= 0 && getTileMap()->getTile(tempX, floor(tempY)) <= 15 )
			{
				go->active = false;
			}
		}
	}

	for (int i = 0; i < CollectiblesList.size(); i++)
	{
		if (CollectiblesList[i]->type == GameObject::GO_KEY_ID && CollectiblesList[i]->active)
		{
			if((CollectiblesList[i]->pos - CCharacter_Player::GetInstance()->getPosition()).Length() < 1)
			{
				CollectiblesList[i]->active = false;
				KEYCOUNT++;
				break;
			}
		}

		
	}


	//for testing
	if (commands[CHECK])
	{
		string line;
		float x, y, z;
		ifstream playerPos("savepoint.txt");

		if (playerPos.is_open())
		{
			while (getline(playerPos, line))
			{
				cout << line << '\n';
			}
			playerPos.close();
		}
		else
			cout << "unable to open file";
	}
	
	//SAVE_ID waypoint
	for (int i = 0; i < InteractionList.size(); i++)
	{
		if (InteractionList[i]->type == GameObject::GO_SAVE && InteractionList[i]->active)
		{
			if ((InteractionList[i]->pos - CCharacter_Player::GetInstance()->getPosition()).Length() < 1)
			{
				cout << "player position saved! " << endl;
				ofstream playerPos("savepoint.txt");
				if (playerPos.is_open())
				{
					//playerPos << CCharacter_Player::GetInstance()->getPosition().Length();
					playerPos << getNewPlayerPos().x << endl;
					playerPos << getNewPlayerPos().y << endl;
					playerPos << getNewPlayerPos().z << endl;

					playerPos.close();
				}
				break;
			}
		}
	}

	switch ( CCharacter_Player::GetInstance()->getState())
	{
	case 0:
		if ( CCharacter_Player::GetInstance()->getAmmoType() == 0 )
		{
			AniToUpdate = PISTOL_IDLE;
		}
		else if ( CCharacter_Player::GetInstance()->getAmmoType() == 1 )
		{
			AniToUpdate = RIFLE_IDLE;
		}
		else if ( CCharacter_Player::GetInstance()->getAmmoType() == 2 )
		{
			AniToUpdate = SHOTGUN_IDLE;
		}
		break;
	case 2:
		if ( CCharacter_Player::GetInstance()->getAmmoType() == 0 )
		{
			AniToUpdate = PISTOL_RELOAD;
		}
		else if ( CCharacter_Player::GetInstance()->getAmmoType() == 1 )
		{
			AniToUpdate = RIFLE_RELOAD;
		}
		else if ( CCharacter_Player::GetInstance()->getAmmoType() == 2 )
		{
			AniToUpdate = SHOTGUN_RELOAD;
		}
		break;
	case 3:
		if ( CCharacter_Player::GetInstance()->getAmmoType() == 0 )
		{
			AniToUpdate = PISTOL_SHOOT;
		}
		else if ( CCharacter_Player::GetInstance()->getAmmoType() == 1 )
		{
			AniToUpdate = RIFLE_SHOOT;
		}
		else if ( CCharacter_Player::GetInstance()->getAmmoType() == 2 )
		{
			AniToUpdate = SHOTGUN_SHOOT;
		}
		break;
	}

	// *?* *?* *?*  *?* *?* *?*  *?* *?* *?*  *?* *?* *?*  *?* *?* *?* Animations *?* *?* *?*  *?* *?* *?*  *?* *?* *?*  *?* *?* *?*  *?* *?* *?* //
	SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(meshList[AniToUpdate]);
	if(sa)
	{
		sa->Update(dt);
	} 
	EnemyDecision(dt);
	GhettoFogOfWar(dt);
	cameraZoom(dt);
	BulletUpdate(dt);
	for (int count = 0; count < NUM_COMMANDS; ++count)
	{
		commands[count] = false;
	}
	FPS = (float)(1.f / dt);
}

void GameModel2D::EnemyDecision(double dt)
{
	for (std::vector<CCharacter_Enemy *>::iterator it = EnemyList.begin(); it != EnemyList.end(); ++it)
	{
		CCharacter_Enemy *go = (CCharacter_Enemy *)*it;
		if ( go->getActive() )
		{
			//test
			//cout << CCharacter_Player::GetInstance()->getAlertState() << ":" << CCharacter_Player::GetInstance()->getDetectionLevel() << endl;

			if ( CCharacter_Player::GetInstance()->getAlertState() == CCharacter_Player::DETECTED )
			{
				//Send all enemies to last seen position
				if ( !CCharacter_Player::GetInstance()->getDetected() )
				{
					CCharacter_Player::GetInstance()->TrackedPosition = CCharacter_Player::GetInstance()->getPosition();
					CCharacter_Player::GetInstance()->SetDetected(true);
				}
				//Set all enemies except cameras to check last seen position
				if ( go->getAmmoType() != go->CAMERA && go->detectPlayer(CCharacter_Player::GetInstance()->getPosition(),getTileMap()))
				{
					//go->setNewState(go->CHECKING);
					go->setNewState(go->ATTACKING);
				}
			}

			VeryRealRaycasting(dt);	

			switch ( go->getState() )
			{
			case CCharacter_Enemy::CHASING:
				{
					go->Strategy_Chaseplayer(CCharacter_Player::GetInstance()->getPosition(),getTileMap());
					break;
				}
			case CCharacter_Enemy::RUNNING:
				{
					go->Strategy_Pathfind(go->getInitPosition(),getAITileMap());
					break;
				}
			case CCharacter_Enemy::SCANNING:
				{
					go->Strategy_Scan(dt);
					break;
				}
			case CCharacter_Enemy::ATTACKING:
				{
					if (go->getAmmoType() != 0)
					{
						//Enemy Shooting (EBullet spawning)
						if (EPistol::GetInstance()->GetFireCooldown() <= 0.0f)
						{
							//Spawn bullet
							SpawnEnemyBullet(go->getPosition(),(go->getTargetPosition()-go->getPosition()).Normalized() * EPistol::GetInstance()->GetBulletSpeed());
							//Reset fire cooldown
							EPistol::GetInstance()->ResetCooldown();
						}
					}
					break;
				}
			case CCharacter_Enemy::TRACKING:
				{
					go->Strategy_Track(dt);	
					break;
				}
			case CCharacter_Enemy::CHECKING:
				{
					go->Strategy_Pathfind(CCharacter_Player::GetInstance()->TrackedPosition,getAITileMap());
					break;
				}
			};
			//go->UpdateEnemyPosition(dt);
			go->Update(dt,getTileMap());
		}
	}

	//Enemy AI Flocking
	for (unsigned i = 0; i < EnemyList.size(); ++i)
	{
		if (EnemyList[i]->getActive())
		{
			/*
			if (CCharacter_Player::GetInstance()->getPosition().x < EnemyList[i]->getPosition().x + 0.5f &&
			CCharacter_Player::GetInstance()->getPosition().x  > EnemyList[i]->getPosition().x - 0.5f &&
			CCharacter_Player::GetInstance()->getPosition().y  < EnemyList[i]->getPosition().y + 0.5f &&
			CCharacter_Player::GetInstance()->getPosition().y > EnemyList[i]->getPosition().y - 0.5f)
			{
			EnemyList[i]->setPosition(EnemyList[i]->getPosition().x + 0.1f, EnemyList[i]->getPosition().y + 0.1f, 0);
			}*/
			for (unsigned j = i; j < EnemyList.size() - j; j++)
			{
				if (EnemyList[j]->getPosition().x < EnemyList[j + 1]->getPosition().x + 0.5f &&
					EnemyList[j]->getPosition().x > EnemyList[j + 1]->getPosition().x - 0.5f &&
					EnemyList[j]->getPosition().y < EnemyList[j + 1]->getPosition().y + 0.5f &&
					EnemyList[j]->getPosition().y > EnemyList[j + 1]->getPosition().y - 0.5f)
				{
					EnemyList[j]->setPosition(EnemyList[j]->getPosition().x + 0.1f, EnemyList[j]->getPosition().y + 0.1f, 0);
					EnemyList[j + 1]->setPosition(EnemyList[j + 1]->getPosition().x - 0.1f, EnemyList[j + 1]->getPosition().y - 0.1f, 0);
				}
			}
		}
	}
}

void GameModel2D::cameraZoom(double dt)
{
	Vector3 initialCam;
	initialCam.Set(camera.position.x, camera.position.y, camera.position.z);
	Vector3 playerPos;
	playerPos.Set(CCharacter_Player::GetInstance()->getPosition().x, CCharacter_Player::GetInstance()->getPosition().y, 20);
	
	if (camera.position.Length() != 0 && ZoomIN)
	{
		if (!(playerPos - initialCam).IsZero())
		{
			camera.position += (playerPos - initialCam).Normalized() * (playerPos - initialCam).Length() * 2.0f * dt;
			camera.target += (playerPos - initialCam).Normalized() * (playerPos - initialCam).Length() * 2.0f * dt;
		}
	}
	//Camera zoom in to player
	if (commands[ENTER] && !ZoomIN)
	{
		ZoomIN = true;
	}
}

float GameModel2D::getFPS()
{
	return FPS;
}

void GameModel2D::setCommands(int command)
{
	if (command >= 0 && command < NUM_COMMANDS)
		commands[command] = true;
}

Mesh* GameModel2D::getTextMesh()
{
	return meshList[TEXT];
}

Mesh* GameModel2D::getBackgroundMesh()
{
	return meshList[BACKGROUND];
}

Mesh* GameModel2D::getCrosshairMesh()
{
	return meshList[CROSSHAIR];
}

Mesh* GameModel2D::getBulletMesh()
{
	return meshList[BULLET];
}

Mesh* GameModel2D::getEBulletMesh()
{
	return meshList[EBULLET];
}

void GameModel2D::BulletUpdate(double dt)
{

	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if ((go->type == GameObject::GO_BULLET || go->type == GameObject::GO_EBULLET) && go->active)
		{
			go->pos += go->vel * 20.f * dt;
			//std::cout << go->pos << std::endl;
		}
	}
}


void GameModel2D::SpawnBullet(int WeaponDamage, float Speed)
{
	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if ( !go->active )
		{
			go->type = GameObject::GO_BULLET;
			go->active = true;
			go->scale.Set(0.05,0.05,0.05);
			go->pos.Set(CCharacter_Player::GetInstance()->getPosition().x, CCharacter_Player::GetInstance()->getPosition().y, CCharacter_Player::GetInstance()->getPosition().z);
			Vector3 tempVel;
			tempVel = (getPos() - CCharacter_Player::GetInstance()->getPosition()).Normalized();
			go->vel = tempVel * Speed;
			go->WDamage = WeaponDamage;
			break;
		}
	}
}

void GameModel2D::SpawnSGBullets(int WeaponDamage, float Speed)
{
	//float ANGLE = Math::RadianToDegree(atan2(getPos().y - CCharacter_Player::GetInstance()->getPosition().y, getPos().x - CCharacter_Player::GetInstance()->getPosition().x));
	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (!go->active)
		{
			go->type = GameObject::GO_BULLET;
			go->active = true;
			go->scale.Set(0.05, 0.05, 0.05);
			go->pos.Set(CCharacter_Player::GetInstance()->getPosition().x, CCharacter_Player::GetInstance()->getPosition().y, CCharacter_Player::GetInstance()->getPosition().z);
			Vector3 tempVel;
			tempVel = (getPos() - CCharacter_Player::GetInstance()->getPosition()).Normalized();
			tempVel.x = Math::RandFloatMinMax(tempVel.x - 0.2f, tempVel.x + 0.2f);
			tempVel.y = Math::RandFloatMinMax(tempVel.y - 0.2f, tempVel.y + 0.2f);
			go->vel = tempVel * Speed;
			go->WDamage = WeaponDamage;
			break;
		}
	}
}

void GameModel2D::SpawnEnemyBullet(Vector3 EnemyPos, Vector3 Vel)
{
	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (!go->active)
		{
			go->type = GameObject::GO_EBULLET;
			go->active = true;
			go->scale.Set(0.05, 0.05, 0.05);
			go->pos = EnemyPos;
			Vector3 tempVel;
			tempVel = Vel;
			go->vel = tempVel * 0.1f;
			break;

		}
	}
}


GameObject* GameModel2D::FetchGO()
{
	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (!go->active)
		{
			go->active = true;
			return go;
		}
	}
	for (unsigned i = 0; i < 10; ++i)
	{
		GameObject *go = new GameObject(GameObject::GO_BULLET);
		m_goList.push_back(go);
	}
	GameObject *go = m_goList.back();
	go->active = true;
	return go;
}

std::vector<GameObject *> GameModel2D::getGameObjectList()
{
	return m_goList;
}

void GameModel2D::getOffset(float& mapOffset_x, float& mapOffset_y)
{
	//mapOffset_x = m_mapOffset_x;
	//mapOffset_y = m_mapOffset_y;
}

TileMap* GameModel2D::getTileMap()
{
	return m_tileMap;
}

TileMap* GameModel2D::getRearTileMap()
{
	return m_ReartileMap;
}

TileMap* GameModel2D::getAITileMap()
{
	return m_AItilemap;
}

Mesh* GameModel2D::getTileMesh()
{
	return meshList[TILE];
}

Mesh* GameModel2D::getFloorTileMesh()
{
	return meshList[TILEFLOOR];
}

Mesh* GameModel2D::getPlayerMesh(GEOMETRY_TYPE meshToTake)
{
	switch (meshToTake)
	{
	case PISTOL_IDLE:
		return meshList[PISTOL_IDLE];
		break;
	case PISTOL_RELOAD:
		return meshList[PISTOL_RELOAD];
		break;
	case PISTOL_SHOOT:
		return meshList[PISTOL_SHOOT];
		break;
	case RIFLE_IDLE:
		return meshList[RIFLE_IDLE];
		break;
	case RIFLE_RELOAD:
		return meshList[RIFLE_RELOAD];
		break;
	case RIFLE_SHOOT:
		return meshList[RIFLE_SHOOT];
		break;
	case SHOTGUN_IDLE:
		return meshList[SHOTGUN_IDLE];
		break;
	case SHOTGUN_RELOAD:
		return meshList[SHOTGUN_RELOAD];
		break;
	case SHOTGUN_SHOOT:
		return meshList[SHOTGUN_SHOOT];
		break;
	}
}

Mesh* GameModel2D::getEnemyMesh(GEOMETRY_TYPE meshToTake)
{
	switch (meshToTake)
	{
	case ALERT:
		return meshList[ALERT];
		break;
	case CAUTION:
		return meshList[CAUTION];
		break;
	case ENEMY_CAMERA:
		return meshList[ENEMY_CAMERA];
		break;
	case ENEMY_LIGHT_IDLE:
		return meshList[ENEMY_LIGHT_IDLE];
		break;
	}
}

std::vector<CCharacter_Enemy*> GameModel2D::getEnemyList()
{
	return EnemyList;
}

std::vector<GameObject*> GameModel2D::getCollectiblesList()
{
	return CollectiblesList;
}

std::vector<GameObject*> GameModel2D::getInteractionList()
{
	return InteractionList;
}

Mesh* GameModel2D::getMobsMesh()
{
	return meshList[MOBS];
}

int GameModel2D::getScore()
{
	return score;
}

int GameModel2D::getCDTimer()
{
	return CDTimer;
}

Vector3 GameModel2D::getNewPlayerPos()
{
	return newPlayerPos;
}

Vector3 GameModel2D::getNewExitPos()
{
	return newExitPos;
}

void GameModel2D::setNewPlayerPos(float x, float y, float z)
{
	if ( !newLevel )
	{
		newPlayerPos.Set(x,y,z);
		SpawnReady = true;
		newLevel = true;
	}
}

void GameModel2D::setNewExitPos(float x, float y, float z)
{
	newExitPos.Set(x,y,z);
}

Mesh* GameModel2D::getWallMesh()
{
	return meshList[CUBE];
}

Mesh* GameModel2D::getTextPrompt()
{
	return meshList[TEXT_PROMPT];
}

Mesh* GameModel2D::getHealth()
{
	return meshList[HEALTH];
}

Mesh* GameModel2D::getHealthBar()
{
	return meshList[HEALTH_BAR];
}

Mesh* GameModel2D::getPistolIcon()
{
	return meshList[PISTOL_ICON];
}

Mesh* GameModel2D::getRifleIcon()
{
	return meshList[RIFLE_ICON];
}

Mesh* GameModel2D::getShotgunIcon()
{
	return meshList[SHOTGUN_ICON];
}

Mesh* GameModel2D::getPistolAmmo()
{
	return meshList[PISTOL_AMMO];
}

Mesh* GameModel2D::getRifleAmmo()
{
	return meshList[RIFLE_AMMO];
}

Mesh* GameModel2D::getShotgunAmmo()
{
	return meshList[SHOTGUN_AMMO];
}

Mesh* GameModel2D::getFogOfWar()
{
	return meshList[FOG];
}

void GameModel2D::setNewEnemy(float x, float y, float z, int ID)
{
	for ( unsigned i = 0; i < EnemyList.size(); ++i)
	{
		if ( !EnemyList[i]->getActive())
		{
			EnemyList[i]->setActive(true);
			EnemyList[i]->setPosition(x,y,z);
			EnemyList[i]->setID(ID);
			EnemyList[i]->setGroupID(m_EnemySpawnCount);
			EnemyList[i]->setRotation(180);
			EnemyList[i]->pathfind_tilemap = getAITileMap();
			EnemyList[i]->CreateGrid();
			m_EnemySpawnCount++;
			switch ( ID )
			{
			case 0:
				EnemyList[i]->setAmmoType(CCharacter_Enemy::CAMERA);
				EnemyList[i]->setNewState(CCharacter_Enemy::SCANNING);
				break;
			case 1:
				EnemyList[i]->setAmmoType(CCharacter_Enemy::FLASHLIGHT);
				EnemyList[i]->setNewState(CCharacter_Enemy::IDLE);
				break;
			};
			break;
		}
	}
}

void GameModel2D::setNewCollectible(Vector3 Pos,Vector3 Scale,GameObject::GAMEOBJECT_TYPE type,int spriteCol, int spriteRow)
{
	for (std::vector<GameObject *>::iterator it = CollectiblesList.begin(); it != CollectiblesList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		{
			if ( !go->active )
			{
				go->active = true;
				go->pos = Pos;
				go->scale = Scale;
				go->type = type;
				go->SpriteRow = spriteRow;
				go->SpriteColumn = spriteCol;
				break;
			}
		}
	}
}

void GameModel2D::setNewInteraction(Vector3 Pos,Vector3 Scale,GameObject::GAMEOBJECT_TYPE type,int spriteCol, int spriteRow)
{
	for (std::vector<GameObject *>::iterator it = InteractionList.begin(); it != InteractionList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		{
			if ( !go->active )
			{
				go->active = true;
				go->pos = Pos;
				go->scale = Scale;
				go->type = type;
				go->SpriteRow = spriteRow;
				go->SpriteColumn = spriteCol;
				break;
			}
		}
	}
}

bool GameModel2D::checkCollision(Vector3 Pos, Vector3 scale, Vector3 Vel, GameObject* go2, double dt)
{
	switch(go2->type)
	{
	case GameObject::GO_WALL:
		{
			//|(w0-b1).N| < r + h / 2
			Vector3 w0 = go2->pos;
			Vector3 b1 = Pos + Vel * dt;
			Vector3 N = go2->normal;
			float r = scale.x;
			float h = go2->scale.x;

			Vector3 NP(-N.y, N.x);
			float l = go2->scale.y;

			if ( (abs((w0-b1).Dot(N))) < r + h * 0.5 && (abs((w0-b1).Dot(NP))) < r + l * 0.5)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		break;
	}
}

void GameModel2D::getMapData()
{
	for (int ccount = 0; ccount < getTileMap()->getNumOfTilesWidth(); ++ccount)
	{
		for (int rcount = 0; rcount < getTileMap()->getNumOfTilesHeight(); ++rcount)
		{
			Vector3 tempPos;
			tempPos.Set(ccount,rcount,0.0f);

			Vector3 tempScale;
			tempScale.Set(1,1,1);
			int Temp = getTileMap()->getTile(ccount, rcount);

			switch ( Temp )
			{
			case GameModel2D::SPAWN_ID:
				{
					setNewPlayerPos(ccount, rcount,0.0f);
				}
				break;
			case GameModel2D::EXIT_ID:
				{
					//setNewExitPos(ccount,rcount,0);
					setNewInteraction(tempPos,tempScale,GameObject::GO_EXIT,ccount,rcount);
				}
				break;
			case GameModel2D::ENEMY_ID:
				{
					if ( ccount%4 == GroupToSpawn || rcount%4 == GroupToSpawn )
					{
					setNewEnemy(ccount,rcount,0,1);
					}
				}
				break;
			case GameModel2D::CAMERA_ID:
				{
					setNewEnemy(ccount,rcount,0,0);
				}
				break;
			case GameModel2D::SAVE_ID:
				{
					setNewInteraction(tempPos,tempScale,GameObject::GO_SAVE,ccount,rcount);
				}
				break;
			case GameModel2D::PC_ID:
				{
					setNewInteraction(tempPos,tempScale,GameObject::GO_PC,ccount,rcount);
				}
				break;
			case GameModel2D::AMMO_ID:
				{
					setNewCollectible(tempPos,tempScale,GameObject::GO_AMMO,ccount,rcount);
				}
				break;
			case GameModel2D::LOCKPICK_ID_2:
				{
					setNewInteraction(tempPos,tempScale,GameObject::GO_LOCKPICK_2,ccount,rcount);
				}
				break;
			case GameModel2D::LOCKPICK_ID_1:
				{
					setNewInteraction(tempPos,tempScale,GameObject::GO_LOCKPICK_1,ccount,rcount);
				}
				break;
			case GameModel2D::KEYUNLOCK_ID:
				{
					setNewInteraction(tempPos,tempScale,GameObject::GO_LOCK_KEY_ID,ccount,rcount);
				}
				break;
			case GameModel2D::KEY_ID:
				{
					setNewCollectible(tempPos,tempScale,GameObject::GO_KEY_ID,ccount,rcount);
				}
				break;
			case GameModel2D::LASER_HORI_ID:
				{
					setNewCollectible(tempPos,tempScale,GameObject::GO_LASER_HORI,ccount,rcount);
				}
				break;
			case GameModel2D::LASER_VERTI_ID:
				{
					setNewCollectible(tempPos,tempScale,GameObject::GO_LASER_VERTI,ccount,rcount);
				}
				break;
			}
		}
	}
}

void GameModel2D::objective(void)
{
	switch ( m_CurrentLevel )
	{
	case 1:
		m_ObjectiveCleared = true;
		break;
	case 2:
		m_ObjectiveCleared = true;
		//vehicle tracked
		break;
	case 3:
		m_ObjectiveCleared = true;
		//data got
		break;
	case 4:
		m_ObjectiveCleared = true;
		//boss died
		break;
	}
}

bool GameModel2D::getObjectiveCleared(void)
{
	return m_ObjectiveCleared;
}

Mesh* GameModel2D::getLockPickBG()
{
	return meshList[LOCKPICKBG];
}

Mesh* GameModel2D::getLockPickBar()
{
	return meshList[LOCKPICKBAR];
}

Mesh* GameModel2D::getLockPickBall()
{
	return meshList[LOCKPICKBALL];
}

bool GameModel2D::getLockPick1()
{
	return InLockPick1;
}

bool GameModel2D::getLockPick2()
{
	return InLockPick2;
}

float GameModel2D::getLockPickY()
{
	return LockPickY;
}

std::vector<GameObject *> GameModel2D::getFogList()
{
	return m_fogList;
}

std::vector<GameObject *> GameModel2D::getFogCheckerList()
{
	return m_fogCheckerList;
}

void GameModel2D::GhettoFogOfWar(double dt)
{
	for (int ccount = 0; ccount < getTileMap()->getNumOfTilesWidth(); ++ccount)
	{
		for (int rcount = 0; rcount < getTileMap()->getNumOfTilesHeight(); ++rcount)
		{
			Vector3 tempPos;
			tempPos.Set(ccount,rcount,0.1f);

			if (getTileMap()->getTile(ccount,rcount) == -1 || getTileMap()->getTile(ccount,rcount) > 15 )
			{
				for (std::vector<GameObject *>::iterator it = m_fogList.begin(); it != m_fogList.end(); ++it)
				{
					GameObject *go = (GameObject *)*it;
					{
						if ( !go->active )
						{
							go->active = true;
							go->pos = tempPos;
							//go->scale = Scale;
							go->type = go->GO_FOG;
							go->SpriteRow = rcount;
							go->SpriteColumn = ccount;
							break;
						}
					}
				}
			}
		}
	}
}
