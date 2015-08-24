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
	meshList[TEXT]->textureID[0] = LoadTGA("Image//Font.tga");
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
	meshList[CUBE] = MeshBuilder::GenerateCube("Bullet", Color(1, 0, 0),1.0f);

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

	//Animation Init
	SpriteAnimation *eENEMY_LIGHT_IDLE = dynamic_cast<SpriteAnimation*>(meshList[ENEMY_LIGHT_IDLE]);
	if(eENEMY_LIGHT_IDLE)
	{
		eENEMY_LIGHT_IDLE->m_anim = new Animation();
		//Start frame, end frame, repeat, time
		eENEMY_LIGHT_IDLE->m_anim->Set(0, 19, 0, 2.0f);
	} 

	SpriteAnimation *eENEMY_CAMERA = dynamic_cast<SpriteAnimation*>(meshList[ENEMY_CAMERA]);
	if(eENEMY_CAMERA)
	{
		eENEMY_CAMERA->m_anim = new Animation();
		//Start frame, end frame, repeat, time
		eENEMY_CAMERA->m_anim->Set(0, 0, 0, 2.0f);
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
	ZoomIN = false;
	SpawnReady = false;
	newLevel = false;
	//BulletShoot = false;
	hasReadLoc = false;
	AniToUpdate = PISTOL_IDLE;
	GroupToSpawn = Math::RandIntMinMax(1,4);

	for ( unsigned i = 0; i < 1000; ++i)
	{
		GameObject * go = new GameObject(GameObject::GO_NONE);
		m_goList.push_back(go);
	}
	for ( unsigned i = 0; i < 100; ++i)
	{
		GameObject * collectibles = new GameObject(GameObject::GO_NONE);
		CollectiblesList.push_back(collectibles);
		GameObject * interact = new GameObject(GameObject::GO_NONE);
		InteractionList.push_back(interact);
		CCharacter_Enemy * enemy = new CCharacter_Enemy();
		EnemyList.push_back(enemy);
	}
}

void GameModel2D::Update(double dt)
{
	if (ZoomIN)
	{
		if (commands[MOVE_UP]) CCharacter_Player::GetInstance()->moveUp();
		if (commands[MOVE_DOWN]) CCharacter_Player::GetInstance()->moveDown();
		if (commands[MOVE_LEFT]) CCharacter_Player::GetInstance()->moveLeft();
		if (commands[MOVE_RIGHT]) CCharacter_Player::GetInstance()->moveRight();
	}

	CCharacter_Player::GetInstance()->Update(dt,getTileMap());
	//Weapon changing
	int CurrentWeapon = CCharacter_Player::GetInstance()->getAmmoType();
	if (commands[PREVWEAP])CurrentWeapon--;
	if (commands[NEXTWEAP])CurrentWeapon++;

	CCharacter_Player::GetInstance()->setAmmoType(CurrentWeapon);

	//Shooting (Bullet spawning)
	if (commands[SHOOT])
	{
		switch (CCharacter_Player::GetInstance()->getAmmoType())
		{
		case 0:
			if (CPistol::GetInstance()->GetAmmo() > 0)
			{
				//Get Damage
				CPistol::GetInstance()->GetDamage();
				//spawn bullet damage(int) vel(vec3)
				//SpawnBullet(1, );
			}
			break;
		}
	}
	else if (!commands[SHOOT])
	{
	}

	//Enemy update
	for (std::vector<CCharacter_Enemy *>::iterator it = EnemyList.begin(); it != EnemyList.end(); ++it)
	{
		CCharacter_Enemy *go = (CCharacter_Enemy *)*it;
		if ( go->getActive() )
		{
			if ( go->detectPlayer(CCharacter_Player::GetInstance()->getPosition()) )
			{
				switch ( go->getState() )
				{
				case go->CHASING:
					{
						go->Strategy_Chaseplayer(CCharacter_Player::GetInstance()->getPosition());
						break;
					}
				case go->RUNNING:
					{
						go->Strategy_Return();
						break;
					}
				};
			}

			if ( go->getAmmoType() == go->CAMERA )
			{
				go->setNewState(go->SCANNING);
			}

			go->Update(dt,getTileMap());
		}
	}
	BulletUpdate(dt);

	//Check against wall
	//for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	//{
	//	GameObject *go = (GameObject *)*it;
	//	if ( go->active )
	//	{
	//		if ( checkCollision(CCharacter_Player::GetInstance()->getPosition(),CCharacter_Player::GetInstance()->getScale(),CCharacter_Player::GetInstance()->getVelocity(),go,dt) )
	//		{
	//			//broken collision
	//			//std::cout << " touche " << std::endl;
	//		}
	//	}
	//}

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

	for (int count = 0; count < NUM_COMMANDS; ++count)
		commands[count] = false;

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
void GameModel2D::BulletUpdate(double dt)
{

	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go->type == GameObject::GO_BULLET && go->active)
		{
			go->pos += go->vel * 20.f * dt;
			//std::cout << go->pos << std::endl;
		}
	}
}


void GameModel2D::SpawnBullet(int WeaponDamage, Vector3 Velocity)
{

	float ANGLE = Math::RadianToDegree(atan2(getPos().y - CCharacter_Player::GetInstance()->getPosition().y,getPos().x - CCharacter_Player::GetInstance()->getPosition().x));

	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if ( !go->active )
		{
			std::cout << " shoot " << std::endl;
			go->type = GameObject::GO_BULLET;
			go->active = true;
			go->scale.Set(0.05,0.05,0.05);
			go->pos.Set(CCharacter_Player::GetInstance()->getPosition().x, CCharacter_Player::GetInstance()->getPosition().y, CCharacter_Player::GetInstance()->getPosition().z);
			Vector3 tempVel;
			tempVel = (getPos() - CCharacter_Player::GetInstance()->getPosition()).Normalized();
			go->vel = tempVel;
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

void GameModel2D::setNewEnemy(float x, float y, float z, int ID)
{
	for ( unsigned i = 0; i < EnemyList.size(); ++i)
	{
		if ( !EnemyList[i]->getActive())
		{
			EnemyList[i]->setActive(true);
			EnemyList[i]->setPosition(x,y,z);
			EnemyList[i]->setID(ID);
			EnemyList[i]->setRotation(180);
			switch ( ID )
			{
			case 0:
				EnemyList[i]->setAmmoType(CCharacter_Enemy::CAMERA);
				break;
			case 1:
				EnemyList[i]->setAmmoType(CCharacter_Enemy::FLASHLIGHT);
				break;
			};
			EnemyList[i]->setNewState(CCharacter_Enemy::IDLE);
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
			tempPos.Set(ccount,rcount,0.1f);

			Vector3 tempScale;
			tempScale.Set(1,1,1);
			int Temp = getTileMap()->getTile(ccount, rcount);

			switch ( Temp )
			{
			case GameModel2D::SPAWN_ID:
				{
					setNewPlayerPos(ccount, rcount,-0.8f);
				}
				break;
			case GameModel2D::EXIT_ID:
				{
					setNewExitPos(ccount,rcount,0);
				}
				break;
			case GameModel2D::ENEMY_ID:
				{
					//if ( Math::RandIntMinMax(1,4) == Temp )
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