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
		RenderMobsDetection();
		RenderScene();
		RenderTileMap();
		RenderMobs();
		RenderFog();
		if (model->isZoomed)
		{
			RenderPlayerRadius();
		}
		//RenderHealth();
		RenderKeysIcon();
		RenderKeys();
		//RenderHBar();
		RenderCountDownTimer();
		RenderCountDownTimerIcon();
		RenderPlayerFace();
		RenderPlayerDetectStatus();
		RenderUI();
		RenderScore();
			switch (CCharacter_Player::GetInstance()->getAmmoType())
		{
		case 0:
			RenderPistolIcon();
			RenderPistolAmmo();
			RenderPACount();
			RenderPAStored();
			break;
		case 1:
			RenderRifleIcon();
			RenderRifleAmmo();
			RenderRACount();
			RenderRAStored();
			break;
		case 2:
			RenderShotgunIcon();
			RenderShotgunAmmo();
			RenderSACount();
			RenderSAStored();
			break;
		}
		if (model->getLockPick1())
		{
			RenderLockPick();
			RenderLockBarRed();
			RenderLockBall();
		}
		if (model->getLockPick2())
		{
			RenderLockPick();
			RenderLockBarBlue();
			RenderLockBall();
		}
		if (model->getNearLock())
		{
			RenderPrompt();
		}
		RenderCrosshair();
		
		RenderPlayerCharacter();
		//Gameobjects
			
			RenderOverlay();

		if (model->m_resultScreen)
		{
			RenderTotalScore();
		}
		glEnable(GL_DEPTH_TEST);
	}
	modelStack.PopMatrix();
}

void GameView2D::RenderPlayerRadius()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	modelStack.PushMatrix(); 
	modelStack.Translate(CCharacter_Player::GetInstance()->getPosition().x, CCharacter_Player::GetInstance()->getPosition().y, 0);
	modelStack.Scale(40,40,0);
	RenderMesh(model->getPlayerRadius(), false);
	modelStack.PopMatrix();
}

void GameView2D::RenderFog()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	std::vector<GameObject*> tempList = model->getGameObjectList();
	std::vector<GameObject*> fogList = model->getFogList();
	for (std::vector<GameObject *>::iterator it = fogList.begin(); it != fogList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go->active)
		{
			if ( go->type == go->GO_FOG  || go->type == go->GO_EXPLORED_FOG)
			{
				RenderGO(go,tileMap);
			}
		}
	}
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
			if ( go->type != go->GO_EXIT )
			{
				RenderGO(go,tileMap);
			}
			else if ( model->getObjectiveCleared() )
			{
				RenderGO(go,tileMap);
			}
		}
	}

	std::vector<GameObject*> fogList = model->getFogCheckerList();
	for (std::vector<GameObject *>::iterator it = fogList.begin(); it != fogList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go->active)
		{
				//RenderGO(go,tileMap);
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
			modelStack.Translate(ccount, rcount, 0.00f);
			Vector3 tempPos;
			tempPos.Set(ccount,rcount,0.1f);
			Vector3 tempScale;
			tempScale.Set(1,1,1);
			int Temp = tileMap->getTile(ccount, rcount);
			if ( Temp <= 15 || Temp >= 20 && Temp <= 23)
			{
				RenderMesh(model->getTileMesh(), false, 6 * tileMap->getTile(ccount, rcount), 6);
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
	modelStack.Translate(0, 0, 0);
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
		case 1:
			if (CCharacter_Player::GetInstance()->getAmmoType() == 0)
			{
				RenderMeshSprite(model->getPlayerMesh(model->PISTOL_RELOAD), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6);
			}
			else if (CCharacter_Player::GetInstance()->getAmmoType() == 1)
			{
				RenderMeshSprite(model->getPlayerMesh(model->RIFLE_RELOAD), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6);
			}
			else if (CCharacter_Player::GetInstance()->getAmmoType() == 2)
			{
				RenderMeshSprite(model->getPlayerMesh(model->SHOTGUN_RELOAD), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6);
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

void GameView2D::RenderMobsDetection()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	std::vector<CCharacter_Enemy*> EnemyList = model->getEnemyList();
	for (std::vector<CCharacter_Enemy *>::iterator it = EnemyList.begin(); it != EnemyList.end(); ++it)
	{
		CCharacter_Enemy *go = (CCharacter_Enemy *)*it;

		modelStack.PushMatrix();
		modelStack.Translate(go->getPosition().x ,go->getPosition().y,0.0f);
		modelStack.Rotate(go->getRotation() + 90,0,0,1);
		modelStack.Scale(CCharacter_Enemy::FOVdistance * 0.75f,CCharacter_Enemy::FOVdistance * 2.1f,1);
		if (go->getActive() && go->m_Render)
		{
			RenderMesh(model->getMeshTaker(model->ENEMY_CONE), false);
		}
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(go->DetectionCornerL.x,go->DetectionCornerL.y,0.0f);
		modelStack.Rotate(go->m_RotationArcMin,0,0,1);
		modelStack.Scale(CCharacter_Enemy::FOVdistance,0.05,0.05);
		if (go->getActive() && go->m_Render)
		{
			//RenderMesh(model->getWallMesh(), false);
		}
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(go->DetectionCornerR.x,go->DetectionCornerR.y,0.0f);
		modelStack.Rotate(go->m_RotationArcMax,0,0,1);
		modelStack.Scale(CCharacter_Enemy::FOVdistance,0.05,0.05);
		if (go->getActive() && go->m_Render)
		{
			//RenderMesh(model->getWallMesh(), false);
		}
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(go->DetectionCornerM.x,go->DetectionCornerM.y,0.0f);
		modelStack.Rotate(go->getRotation() + 90.f,0,0,1);
		float tempCalc = (float)CCharacter_Enemy::FOVArc/30.f * (float)CCharacter_Enemy::FOVdistance;
		modelStack.Scale(tempCalc,0.05,0.05);
		if (go->getActive() && go->m_Render)
		{
			//RenderMesh(model->getWallMesh(), false);
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
		modelStack.Translate(go->getPosition().x,go->getPosition().y,0.0f);
		modelStack.Rotate(go->getRotation(),0,0,1);
		if (go->getActive() && go->m_Render)
		{
			switch ( go->getState())
			{
				// idle
			case 0:
				if ( go->getAmmoType() == CCharacter_Enemy::FLASHLIGHT)
				{
					RenderMeshSprite(model->getEnemyMesh(model->ENEMY_LIGHT_IDLE), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );
				}
				break;
				// patrol
			case 1:
				if ( go->getAmmoType() == CCharacter_Enemy::FLASHLIGHT)
				{
					RenderMeshSprite(model->getEnemyMesh(model->ENEMY_LIGHT_IDLE), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );
				}
				break;
				// chasing
			case 2:
				if ( go->getAmmoType() == CCharacter_Enemy::FLASHLIGHT)
				{
					RenderMeshSprite(model->getEnemyMesh(model->ENEMY_LIGHT_IDLE), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );
				}
				break;
				// attacking
			case 3:
				if ( go->getAmmoType() == CCharacter_Enemy::FLASHLIGHT)
				{
					RenderMeshSprite(model->getEnemyMesh(model->ENEMY_LIGHT_IDLE), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );
				}
				break;
				// running
			case 4:
				if ( go->getAmmoType() == CCharacter_Enemy::FLASHLIGHT)
				{
					RenderMeshSprite(model->getEnemyMesh(model->ENEMY_LIGHT_IDLE), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );
				}
				break;
				// scanning
			case 5:
				if ( go->getAmmoType() == CCharacter_Enemy::FLASHLIGHT)
				{
					RenderMeshSprite(model->getEnemyMesh(model->ENEMY_LIGHT_IDLE), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );				
				}
				break;
			case 6:
				if ( go->getAmmoType() == CCharacter_Enemy::FLASHLIGHT)
				{
					RenderMeshSprite(model->getEnemyMesh(model->ENEMY_LIGHT_IDLE), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );			
				}
				break;
			case 7:
				if ( go->getAmmoType() == CCharacter_Enemy::FLASHLIGHT)
				{
					RenderMeshSprite(model->getEnemyMesh(model->ENEMY_LIGHT_IDLE), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );			
				}
				break;
			}

			if (go->getAmmoType() == CCharacter_Enemy::BOSS)
			{
				RenderMeshSprite(model->getEnemyMesh(model->BOSS), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );
			}

			if ( go->getAmmoType() == CCharacter_Enemy::CAMERA)
			{
				RenderMeshSprite(model->getEnemyMesh(model->ENEMY_CAMERA), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );
			}
		}
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(go->getPosition().x,go->getPosition().y + (model->getTileMap()->GetTileSize()/model->getTileMap()->GetTileSize()),0.00f);
		if (go->getActive())
		{
			switch ( go->getState())
			{
				// chasing
			case 2:
				{
					RenderMeshSprite(model->getEnemyMesh(model->ALERT), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );
				}
				break;
				//attacking
			case 3:
				{
					RenderMeshSprite(model->getEnemyMesh(model->ALERT), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );
				}
				break;
				// scanning
			case 5:
				{
					if ( go->getAmmoType() != go->CAMERA)
					{
						RenderMeshSprite(model->getEnemyMesh(model->CAUTION), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );
					}
				}
				break;
				// tracking
			case 6:
				{
					if ( CCharacter_Player::GetInstance()->getAlertState() == CCharacter_Player::DETECTED )
					{
						RenderMeshSprite(model->getEnemyMesh(model->ALERT), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );
					}
					else
					{
						RenderMeshSprite(model->getEnemyMesh(model->CAUTION), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );
					}
				}
				break;
				// checking
			case 7:
				{
					RenderMeshSprite(model->getEnemyMesh(model->CAUTION), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );
				}
				break;
			};
		}
		modelStack.PopMatrix();

		for ( int i = 0; i < go->PathFound.size(); ++i )
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->PathFound[i]->m_WorldPosition.x,go->PathFound[i]->m_WorldPosition.y,0.0f);
			if (go->getActive())
			{
				//RenderMeshSprite(model->getEnemyMesh(model->ENEMY_LIGHT_IDLE), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );		
			}
			modelStack.PopMatrix();
		}
	}
}

void GameView2D::RenderUI()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);

	modelStack.PushMatrix();
	std::ostringstream ss;
	ss << "FPS: " << model->getFPS();
	RenderTextOnScreen(model->getTextMesh(), ss.str(), Color(1, 0, 0.5), 30, 10, 770);
	modelStack.PopMatrix();
}

void GameView2D::RenderScore()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	std::ostringstream ss;
	ss << "Score: " << model->getScore();
	RenderTextOnScreen(model->getTextMesh(), ss.str(), Color(1, 1, 1), 40, windowWidth * 0.1, 50);
}

void GameView2D::RenderTotalScore()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	std::ostringstream ss;
	ss << model->getTotalScore();
	RenderTextOnScreen(model->getTextMesh(), ss.str(), Color(1, 1, 1), 60, windowWidth * 0.355, windowHeight * 0.55);
}

void GameView2D::RenderHighScore()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);

}

void GameView2D::RenderCountDownTimer()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	std::ostringstream ss;
	ss << "Time Left: " << model->getCDTimer();
	RenderTextOnScreen(model->getTextMesh(), ss.str(), Color(1, 1, 1), 40, windowWidth * 0.1, 100);
}

void GameView2D::RenderCountDownTimerIcon()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);

	modelStack.PushMatrix();
	RenderImageOnScreen(model->getCountDownTimerIcon(), 40, 40, windowWidth * 0.05, 125);

	modelStack.PopMatrix();
}

void GameView2D::RenderPlayerDetectStatus()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	std::ostringstream ss;
	switch (CCharacter_Player::GetInstance()->getAlertState())
	{
	case 0:
		ss << "Undetected: " << CCharacter_Player::GetInstance()->getDetectionLevel();
		break;
	case 1:
		ss << "Caution: " << CCharacter_Player::GetInstance()->getDetectionLevel();
		break;
	case 2:
		ss << "Detected: " << CCharacter_Player::GetInstance()->getDetectionLevel();
		break;
	}
	RenderTextOnScreen(model->getTextMesh(), ss.str(), Color(1, 1, 1), 40, windowWidth * 0.1, 150);
}

void GameView2D::RenderPlayerFace()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	modelStack.PushMatrix();
	RenderImageOnScreen(model->getPlayerFace(), 40, 40, windowWidth * 0.05, 175);
	modelStack.PopMatrix();
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

void GameView2D::RenderKeysIcon()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);

	modelStack.PushMatrix();
	RenderImageOnScreen(model->getKeys(), 40, 40, windowWidth * 0.06, windowHeight * 0.68);
	modelStack.PopMatrix();
}

void GameView2D::RenderKeys()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	std::ostringstream ss;
	ss << " x" << model->getKeyCount();

	RenderTextOnScreen(model->getTextMesh(), ss.str(), Color(1, 1, 1), 30, windowWidth * 0.08, windowHeight * .65);

}
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
	case GameObject::GO_EBULLET:
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			RenderMesh(model->getEBulletMesh(), false);
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
	case GameObject::GO_EXIT:
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			RenderMesh(model->getTileMesh(), false, 6 * tileMap->getTile(go->SpriteColumn, go->SpriteRow), 6);
			modelStack.PopMatrix();
		}
		break;
	case GameObject::GO_BAGGAGE:
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			RenderMesh(model->getTileMesh(), false, 6 * tileMap->getTile(go->SpriteColumn, go->SpriteRow), 6);
			modelStack.PopMatrix();
		}
		break;
	case GameObject::GO_BLUE:
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			RenderMesh(model->getTileMesh(), false, 6 * tileMap->getTile(go->SpriteColumn, go->SpriteRow), 6);
			modelStack.PopMatrix();
		}
		break;
	case GameObject::GO_GREEN:
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			RenderMesh(model->getTileMesh(), false, 6 * tileMap->getTile(go->SpriteColumn, go->SpriteRow), 6);
			modelStack.PopMatrix();
		}
		break;
	case GameObject::GO_RED:
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			RenderMesh(model->getTileMesh(), false, 6 * tileMap->getTile(go->SpriteColumn, go->SpriteRow), 6);
			modelStack.PopMatrix();
		}
		break;
	case GameObject::GO_YELLOW:
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			RenderMesh(model->getTileMesh(), false, 6 * tileMap->getTile(go->SpriteColumn, go->SpriteRow), 6);
			modelStack.PopMatrix();
		}
		break;
	case GameObject::GO_BLUE_CAR:
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Rotate(90,0,0,1);
			modelStack.Scale(go->scale.x, go->scale.y * 2.f, go->scale.z);
			RenderMesh(model->getCarMesh(model->CAR_BLUE), false);
			modelStack.PopMatrix();
		}
		break;
	case GameObject::GO_GREEN_CAR:
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Rotate(90,0,0,1);
			modelStack.Scale(go->scale.x, go->scale.y * 2.f, go->scale.z);
			RenderMesh(model->getCarMesh(model->CAR_GREEN), false);
			modelStack.PopMatrix();
		}
		break;
	case GameObject::GO_RED_CAR:
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Rotate(90,0,0,1);
			modelStack.Scale(go->scale.x, go->scale.y * 2.f, go->scale.z);
			RenderMesh(model->getCarMesh(model->CAR_RED), false);
			modelStack.PopMatrix();
		}
		break;
	case GameObject::GO_YELLOW_CAR:
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Rotate(90,0,0,1);
			modelStack.Scale(go->scale.x, go->scale.y * 2.f, go->scale.z);
			RenderMesh(model->getCarMesh(model->CAR_YELLOW), false);
			modelStack.PopMatrix();
		}
		break;
	case GameObject::GO_FOG:
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			RenderMesh(model->getFogOfWar(), false);
			//RenderMesh(model->getFogOfWar(), false, 6 * tileMap->getTile(go->SpriteColumn, go->SpriteRow), 6);
			modelStack.PopMatrix();
		}
		break;
	case GameObject::GO_EXPLORED_FOG:
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			RenderMesh(model->getExploredFogOfWar(), false);
			//RenderMesh(model->getFogOfWar(), false, 6 * tileMap->getTile(go->SpriteColumn, go->SpriteRow), 6);
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

void GameView2D::RenderHelpText()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	modelStack.PushMatrix();
	{
		modelStack.Translate(windowWidth / 17, windowHeight / 26, 0);
		modelStack.Scale(windowWidth / 50, windowHeight / 65, 1);
		Render2DMesh(model->getTextPrompt(), false);
	}
	modelStack.PopMatrix();
}

void GameView2D::RenderHealth()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	modelStack.PushMatrix();
	{
		modelStack.Translate(windowWidth * -0.296, windowHeight / 2.23, 0);
		modelStack.Scale(windowWidth / 56.99, windowHeight / 105, 1);
		Render2DMesh(model->getHealth(), false);
	}
	modelStack.PopMatrix();
}

void GameView2D::RenderHDying()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	modelStack.PushMatrix();
	{
		modelStack.Translate(windowWidth * -0.296, windowHeight / 2.23, 0);
		modelStack.Scale(windowWidth / 56.99, windowHeight / 105, 1);
		Render2DMesh(model->getHealthDying(), false);
	}
	modelStack.PopMatrix();
}

void GameView2D::RenderHBar()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	modelStack.PushMatrix();
	{
		modelStack.Translate((windowWidth * -0.35) + CCharacter_Player::GetInstance()->getHP() * 0.999, windowHeight / 2.2, 0);
		modelStack.Scale(0.20 * CCharacter_Player::GetInstance()->getHP()*0.5, 1.4, 1);
		Render2DMesh(model->getHealthBar(), false);
	}
	modelStack.PopMatrix();
}

void GameView2D::RenderPrompt()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	std::ostringstream ss;
	ss << "Press 'E'";
	RenderTextOnScreen(model->getTextMesh(), ss.str(), Color(1, 1, 1), 30, windowWidth / 5, windowHeight * 0.5);
}

void GameView2D::RenderLockPick()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	modelStack.PushMatrix();
	{
		modelStack.Scale(windowWidth / 4, windowHeight / 3, 1);
		modelStack.Translate(1, 0, 0);
		Render2DMesh(model->getLockPickBG(), false);
	}
	modelStack.PopMatrix();
}

void GameView2D::RenderLockBarRed()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	modelStack.PushMatrix();
	{
		modelStack.Scale(windowWidth / 42, windowHeight / 32, 1);
		modelStack.Translate(6.15f, 0, 0);
		Render2DMesh(model->getLockPickBar(), false);
	}
	modelStack.PopMatrix();
}

void GameView2D::RenderLockBarBlue()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	modelStack.PushMatrix();
	{
		modelStack.Scale(windowWidth / 42, windowHeight / 64, 1);
		modelStack.Translate(6.15f, 0, 0);
		Render2DMesh(model->getLockPickBar(), false);
	}
	modelStack.PopMatrix();
}

void GameView2D::RenderLockBall()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	modelStack.PushMatrix();
	{
		modelStack.Scale(windowWidth / 128, windowHeight / 100, 1);
		modelStack.Translate(18.4, model->getLockPickY(), 0);
		Render2DMesh(model->getLockPickBall(), false);
	}
	modelStack.PopMatrix();
}

void GameView2D::RenderPistolIcon()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	modelStack.PushMatrix();
	{
		modelStack.Translate(windowWidth / 2.7, windowHeight / -3, 0);
		modelStack.Scale(windowWidth / 250, windowHeight / 165, 1);
		Render2DMesh(model->getPistolIcon(), false);
	}
	modelStack.PopMatrix();
}

void GameView2D::RenderRifleIcon()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	modelStack.PushMatrix();
	{
		modelStack.Translate(windowWidth / 2.75, windowHeight / -2.95, 0);
		modelStack.Scale(windowWidth / 250, windowHeight / 165, 1);
		Render2DMesh(model->getRifleIcon(), false);
	}
	modelStack.PopMatrix();
}

void GameView2D::RenderShotgunIcon()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	modelStack.PushMatrix();
	{
		modelStack.Translate(windowWidth / 2.75, windowHeight / -2.95, 0);
		modelStack.Scale(windowWidth / 250, windowHeight / 165, 1);
		Render2DMesh(model->getShotgunIcon(), false);
	}
	modelStack.PopMatrix();
}

void GameView2D::RenderPistolAmmo()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	modelStack.PushMatrix();
	{
		modelStack.Translate(windowWidth / 2.4, windowHeight / -2.75, 0);
		modelStack.Scale(windowWidth / 550, windowHeight / 465, 1);
		Render2DMesh(model->getPistolAmmo(), false);
	}
	modelStack.PopMatrix();
}

void GameView2D::RenderRifleAmmo()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	modelStack.PushMatrix();
	{
		modelStack.Translate(windowWidth / 2.4, windowHeight / -2.75, 0);
		modelStack.Scale(windowWidth / 550, windowHeight / 465, 1);
		Render2DMesh(model->getRifleAmmo(), false);
	}
	modelStack.PopMatrix();
}

void GameView2D::RenderShotgunAmmo()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	modelStack.PushMatrix();
	{
		modelStack.Translate(windowWidth / 2.4, windowHeight / -2.75, 0);
		modelStack.Scale(windowWidth / 550, windowHeight / 465, 1);
		Render2DMesh(model->getShotgunAmmo(), false);
	}
	modelStack.PopMatrix();
}

void GameView2D::RenderPACount()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	std::ostringstream ss;
	ss << " x" << CPistol::GetInstance()->GetAmmo();
	RenderTextOnScreen(model->getTextMesh(), ss.str(), Color(1, 1, 1), 25, windowWidth * 0.91, windowHeight / 12);
}

void GameView2D::RenderRACount()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	std::ostringstream ss;
	ss << " x" << CRifle::GetInstance()->GetAmmo();
	RenderTextOnScreen(model->getTextMesh(), ss.str(), Color(1, 1, 1), 25, windowWidth * 0.91, windowHeight / 12);
}

void GameView2D::RenderSACount()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	std::ostringstream ss;
	ss << " x" << (CShotgun::GetInstance()->GetAmmo()) / 7;
	RenderTextOnScreen(model->getTextMesh(), ss.str(), Color(1, 1, 1), 25, windowWidth * 0.91, windowHeight / 12);
}

void GameView2D::RenderPAStored()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	std::ostringstream ss;
	ss << " Stored:" << CPistol::GetInstance()->GetAmmoStored();
	RenderTextOnScreen(model->getTextMesh(), ss.str(), Color(1, 1, 1), 25, windowWidth * 0.76, windowHeight / 22);
}

void GameView2D::RenderRAStored()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	std::ostringstream ss;
	ss << " Stored:" << CRifle::GetInstance()->GetAmmoStored();
	RenderTextOnScreen(model->getTextMesh(), ss.str(), Color(1, 1, 1), 25, windowWidth * 0.76, windowHeight / 22);
}

void GameView2D::RenderSAStored()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	std::ostringstream ss;
	ss << " Stored:" << (CShotgun::GetInstance()->GetAmmoStored()) / 7;
	RenderTextOnScreen(model->getTextMesh(), ss.str(), Color(1, 1, 1), 25, windowWidth * 0.76, windowHeight / 22);
}

void GameView2D::RenderOverlay()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);

	if (model->m_resultScreen)
	{
		modelStack.PushMatrix();
		{
			//modelStack.Translate(windowWidth / 2, windowHeight / 2, 0);
			//modelStack.Scale(windowWidth / 550, windowHeight / 465, 1);
			modelStack.Scale(windowWidth, windowHeight, 1);
			if ( !model->m_GameLost )
			{
				//Render2DMesh(model->getMeshTaker(model->WIN), false);
				RenderImageOnScreen(model->getMeshTaker(model->WIN), windowWidth, windowHeight, windowWidth * 0.5, windowHeight * 0.5);
			}
			else
			{
				//Render2DMesh(model->getMeshTaker(model->LOSE), false);
				RenderImageOnScreen(model->getMeshTaker(model->LOSE), windowWidth, windowHeight, windowWidth * 0.5, windowHeight * 0.5);
			}
		}
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	{
		//modelStack.Translate(windowWidth / 2, windowHeight / 2, 0);
		//modelStack.Scale(windowWidth / 550, windowHeight / 465, 1);
		modelStack.Scale(windowWidth, windowHeight, 1);
		if ( !model->isZoomed )
		{
			switch ( model->m_CurrentLevel )
			{
			case 1:
				{
				//Render2DMesh(model->getMeshTaker(model->WIN), false);
					RenderImageOnScreen(model->getMeshTaker(model->LV1_LAYOUT), windowWidth, windowHeight, windowWidth * 0.5, windowHeight * 0.5);
				}
				break;
			case 2:
				{
				//Render2DMesh(model->getMeshTaker(model->WIN), false);
					RenderImageOnScreen(model->getMeshTaker(model->LV2_LAYOUT), windowWidth, windowHeight, windowWidth * 0.5, windowHeight * 0.5);
				}
				break;
			case 3:
				{
				//Render2DMesh(model->getMeshTaker(model->WIN), false);
					RenderImageOnScreen(model->getMeshTaker(model->LV3_LAYOUT), windowWidth, windowHeight, windowWidth * 0.5, windowHeight * 0.5);
				}
				break;
			case 4:
				{
				//Render2DMesh(model->getMeshTaker(model->WIN), false);
					RenderImageOnScreen(model->getMeshTaker(model->LV4_LAYOUT), windowWidth, windowHeight, windowWidth * 0.5, windowHeight * 0.5);
				}
				break;
			}
		}
	}
	modelStack.PopMatrix();
}
