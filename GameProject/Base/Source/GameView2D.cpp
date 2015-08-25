#include "GameView2D.h"

GameView2D::GameView2D(Model* model) : View(model)
{
}

#define tileMap model->getTileMap()

void GameView2D::Render()
{
	View::Render();

	Mtx44 perspective;
	//perspective.SetToOrtho(0, 32, 0, 25, -1000, 1000);
	//projectionStack.LoadMatrix(perspective);

	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);

	modelStack.PushMatrix(); 
	{
		//RenderBackground();
		glDisable(GL_DEPTH_TEST);
		RenderRearTileMap();
		RenderScene();
		RenderTileMap();
		RenderMobs();
		glEnable(GL_DEPTH_TEST);
		RenderPlayerCharacter();
		//Gameobjects
		RenderCrosshair();
		//RenderScore();
	} 
	modelStack.PopMatrix();
}

void GameView2D::RenderScene()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	std::vector<GameObject*> tempList = model->getGameObjectList();
	for (std::vector<GameObject *>::iterator it = tempList.begin(); it != tempList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go->active)
		{
			RenderGO(go,tileMap);
		}
	}

	std::vector<GameObject*> collectibleList = model->getCollectiblesList();
	for (std::vector<GameObject *>::iterator it = collectibleList.begin(); it != collectibleList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go->active)
		{
			RenderGO(go,tileMap);
		}
	}

	std::vector<GameObject*> interactionList = model->getInteractionList();
	for (std::vector<GameObject *>::iterator it = interactionList.begin(); it != interactionList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go->active)
		{
			RenderGO(go,tileMap);
		}
	}
}

void GameView2D::RenderBackground()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);

	float mapOffset_x, mapOffset_y;
	model->getOffset(mapOffset_x, mapOffset_y);
	while (mapOffset_x > 64) mapOffset_x -= 64;
	mapOffset_x /= 2;

	modelStack.PushMatrix(); {
		modelStack.Translate(-mapOffset_x, -mapOffset_y, 0);
		modelStack.Scale(32, 25, 1);
		modelStack.Translate(.5, .5, -1);

		RenderMesh(model->getBackgroundMesh(), false);

		modelStack.PushMatrix(); {
			modelStack.Translate(1, 0, 0);

			RenderMesh(model->getBackgroundMesh(), false);
		} modelStack.PopMatrix();
	} modelStack.PopMatrix();
}

void GameView2D::RenderTileMap()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);

	//modelStack.Translate(0, 0, 0.001f);
	for (int ccount = 0; ccount < tileMap->getNumOfTilesWidth(); ++ccount)
	{
		for (int rcount = 0; rcount < tileMap->getNumOfTilesHeight(); ++rcount)
		{
			modelStack.PushMatrix(); 
			modelStack.Translate(ccount, rcount, 0.05f);
			int Temp = tileMap->getTile(ccount, rcount);
			Vector3 tempPos;
			tempPos.Set(ccount,rcount,0.1f);
			Vector3 tempScale;
			tempScale.Set(1,1,1);

			switch ( Temp )
			{
				if ( !model->hasReadLoc )
				{
			case model->SPAWN_ID:
				{
					model->setNewPlayerPos(ccount, rcount,-0.8f);
				}
				break;
			case model->EXIT_ID:
				{
					model->setNewExitPos(ccount,rcount,0);
				}
				break;
			case model->ENEMY_ID:
				{
					model->setNewEnemy(ccount,rcount,0,1);
				}
				break;
			case model->CAMERA_ID:
				{
					model->setNewEnemy(ccount,rcount,0,0);
				}
				break;
			case model->SAVE_ID:
				{
					model->setNewInteraction(tempPos,tempScale,GameObject::GO_SAVE,ccount,rcount);
				}
				break;
			case model->PC_ID:
				{
					model->setNewInteraction(tempPos,tempScale,GameObject::GO_PC,ccount,rcount);
				}
				break;
			case model->AMMO_ID:
				{
					model->setNewCollectible(tempPos,tempScale,GameObject::GO_AMMO,ccount,rcount);
				}
				break;
			case model->LOCKPICK_ID_2:
				{
					model->setNewInteraction(tempPos,tempScale,GameObject::GO_LOCKPICK_2,ccount,rcount);
				}
				break;
			case model->LOCKPICK_ID_1:
				{
					model->setNewInteraction(tempPos,tempScale,GameObject::GO_LOCKPICK_1,ccount,rcount);
				}
				break;
			case model->KEYUNLOCK_ID:
				{
					model->setNewInteraction(tempPos,tempScale,GameObject::GO_LOCK_KEY_ID,ccount,rcount);
				}
				break;
			case model->KEY_ID:
				{
					model->setNewCollectible(tempPos,tempScale,GameObject::GO_KEY_ID,ccount,rcount);
				}
				break;
			case model->LASER_HORI_ID:
				{
					model->setNewCollectible(tempPos,tempScale,GameObject::GO_LASER_HORI,ccount,rcount);
				}
				break;
			case model->LASER_VERTI_ID:
				{
					model->setNewCollectible(tempPos,tempScale,GameObject::GO_LASER_VERTI,ccount,rcount);
				}
				break;
				}
			default :
				{
					if ( tileMap->getTile(ccount, rcount) >= 0 )
					{
						RenderMesh(model->getTileMesh(), false, 6 * tileMap->getTile(ccount, rcount), 6);
					}
				}

			}
			modelStack.PopMatrix();
		}
	}
	model->hasReadLoc = true;
}

#undef tileMap

#define reartileMap model->getRearTileMap()

void GameView2D::RenderRearTileMap()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);

	for (int ccount = 0; ccount < reartileMap->getNumOfTilesWidth(); ++ccount)
	{
		for (int rcount = 0; rcount < reartileMap->getNumOfTilesHeight(); ++rcount)
		{
			modelStack.PushMatrix(); {
				modelStack.Translate(ccount, rcount, 0);
				//modelStack.Translate(0.5f, 0.5f, 0);
				RenderMesh(model->getTileMesh(), false, 6 * reartileMap->getTile(ccount, rcount), 6);
			} modelStack.PopMatrix();
		}
	}
}

#undef reartileMap

void GameView2D::RenderPlayerCharacter()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	float ANGLE = Math::RadianToDegree(atan2(model->getPos().y - CCharacter_Player::GetInstance()->getPosition().y, model->getPos().x - CCharacter_Player::GetInstance()->getPosition().x));
	modelStack.Translate(0, 0, 1);
	modelStack.PushMatrix(); {
		modelStack.Translate(CCharacter_Player::GetInstance()->getPosition());
		//modelStack.Translate(0.5, 0.5, 0);
		modelStack.Rotate(ANGLE,0,0,1);
		switch ( CCharacter_Player::GetInstance()->getState())
		{
		case 0:
			if ( CCharacter_Player::GetInstance()->getAmmoType() == 0 )
			{
				RenderMeshSprite(model->getPlayerMesh(model->PISTOL_IDLE), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );
			}
			else if ( CCharacter_Player::GetInstance()->getAmmoType() == 1 )
			{
				RenderMeshSprite(model->getPlayerMesh(model->RIFLE_IDLE), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );
			}
			else if ( CCharacter_Player::GetInstance()->getAmmoType() == 2 )
			{
				RenderMeshSprite(model->getPlayerMesh(model->SHOTGUN_IDLE), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );
			}
			break;
		case 2:
			if ( CCharacter_Player::GetInstance()->getAmmoType() == 0 )
			{
				RenderMeshSprite(model->getPlayerMesh(model->PISTOL_RELOAD), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );
			}
			else if ( CCharacter_Player::GetInstance()->getAmmoType() == 1 )
			{
				RenderMeshSprite(model->getPlayerMesh(model->RIFLE_RELOAD), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );
			}
			else if ( CCharacter_Player::GetInstance()->getAmmoType() == 2 )
			{
				RenderMeshSprite(model->getPlayerMesh(model->SHOTGUN_RELOAD), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );
			}
			break;
		case 3:
			if ( CCharacter_Player::GetInstance()->getAmmoType() == 0 )
			{
				RenderMeshSprite(model->getPlayerMesh(model->PISTOL_SHOOT), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );
			}
			else if ( CCharacter_Player::GetInstance()->getAmmoType() == 1 )
			{
				RenderMeshSprite(model->getPlayerMesh(model->RIFLE_SHOOT), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );
			}
			else if ( CCharacter_Player::GetInstance()->getAmmoType() == 2 )
			{
				RenderMeshSprite(model->getPlayerMesh(model->SHOTGUN_SHOOT), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );
			}
			break;
		}
		modelStack.PopMatrix();
	}
}

void GameView2D::RenderMobs()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	std::vector<CCharacter_Enemy*> EnemyList = model->getEnemyList();
	for (std::vector<CCharacter_Enemy *>::iterator it = EnemyList.begin(); it != EnemyList.end(); ++it)
	{
		CCharacter_Enemy *go = (CCharacter_Enemy *)*it;
		modelStack.PushMatrix();
		modelStack.Translate(go->getPosition().x,go->getPosition().y,0.01f);
		modelStack.Rotate(go->getRotation(),0,0,1);
		if (go->getActive())
		{
			/*switch ( go->getState())
			{
			case 0:
				if ( go->getAmmoType() == CCharacter_Enemy::FLASHLIGHT )
				{
					RenderMeshSprite(model->getEnemyMesh(model->ENEMY_LIGHT_IDLE), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );
				}
				break;
			}*/
			RenderMeshSprite(model->getEnemyMesh(model->ENEMY_LIGHT_IDLE), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );
		}
		modelStack.PopMatrix();
	}
}

void GameView2D::RenderScore()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);

	std::ostringstream ss;
	ss << "Score: " << model->getScore();
	RenderTextOnScreen(model->getTextMesh(), ss.str(), Color(0, 0, 0), 50, 100, 700);
}

#define player model->getPlayer()
void GameView2D::RenderCrosshair()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	modelStack.PushMatrix();
	{
		modelStack.Scale(windowWidth / 32, windowHeight / 25, 1);
		modelStack.Translate(model->getPos() * 0.032f);
		Render2DMesh(model->getCrosshairMesh(), false);
	}
	modelStack.PopMatrix();
}
#undef player

void GameView2D::RenderGO(GameObject *go, TileMap* tileMap)
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	switch (go->type)
	{
	case GameObject::GO_BULLET:
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			RenderMesh(model->getBulletMesh(), false);
			modelStack.PopMatrix();
		}
		break;
	case GameObject::GO_AMMO:
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			RenderMesh(model->getTileMesh(), false, 6 * tileMap->getTile(go->SpriteColumn, go->SpriteRow), 6);
			modelStack.PopMatrix();
		}
		break;
	case GameObject::GO_SAVE:
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			RenderMesh(model->getTileMesh(), false, 6 * tileMap->getTile(go->SpriteColumn, go->SpriteRow), 6);
			modelStack.PopMatrix();
		}
		break;
	case GameObject::GO_PC:
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			RenderMesh(model->getTileMesh(), false, 6 * tileMap->getTile(go->SpriteColumn, go->SpriteRow), 6);
			modelStack.PopMatrix();
		}
		break;
		case GameObject::GO_LOCKPICK_2:
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			RenderMesh(model->getTileMesh(), false, 6 * tileMap->getTile(go->SpriteColumn, go->SpriteRow), 6);
			modelStack.PopMatrix();
		}
		break;
		case GameObject::GO_LOCKPICK_1:
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			RenderMesh(model->getTileMesh(), false, 6 * tileMap->getTile(go->SpriteColumn, go->SpriteRow), 6);
			modelStack.PopMatrix();
		}
		break;
		case GameObject::GO_LOCK_KEY_ID:
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			RenderMesh(model->getTileMesh(), false, 6 * tileMap->getTile(go->SpriteColumn, go->SpriteRow), 6);
			modelStack.PopMatrix();
		}
		break;
	case GameObject::GO_KEY_ID:
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			RenderMesh(model->getTileMesh(), false, 6 * tileMap->getTile(go->SpriteColumn, go->SpriteRow), 6);
			modelStack.PopMatrix();
		}
		break;
	case GameObject::GO_LASER_HORI:
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			RenderMesh(model->getTileMesh(), false, 6 * tileMap->getTile(go->SpriteColumn, go->SpriteRow), 6);
			modelStack.PopMatrix();
		}
		break;
	case GameObject::GO_LASER_VERTI:
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			RenderMesh(model->getTileMesh(), false, 6 * tileMap->getTile(go->SpriteColumn, go->SpriteRow), 6);
			modelStack.PopMatrix();
		}
		break;
	/*case GameObject::GO_WALL:
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			float angle = Math::RadianToDegree(atan2(go->normal.y,go->normal.x));
			modelStack.Rotate(angle,0,0,1);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			RenderMesh(model->getWallMesh(), false);
			modelStack.PopMatrix();
		}
		break;*/
	}
}
