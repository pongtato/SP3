#include "GameView2D.h"

GameView2D::GameView2D(Model* model) : View(model)
{
}

void GameView2D::Render()
{
	View::Render();

	Mtx44 perspective;
	//perspective.SetToOrtho(0, 32, 0, 25, -1000, 1000);
	//projectionStack.LoadMatrix(perspective);

	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);

	modelStack.PushMatrix(); {
		//RenderBackground();
		RenderMobs();
		RenderRearTileMap();
		RenderTileMap();
		RenderPlayerCharacter();
		RenderCrosshair();
		//RenderScore();
	} modelStack.PopMatrix();

	//Gameobjects
	std::vector<GameObject*> tempList = model->getGameObjectList();
	for (std::vector<GameObject *>::iterator it = tempList.begin(); it != tempList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go->active)
		{
			RenderGO(go);
		}
	}

	for (int count = 0; count < model->getBulletShoot(); count++)
	{
		model->SpawnBullet();
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

#define tileMap model->getTileMap()

void GameView2D::RenderTileMap()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);

	glDisable(GL_DEPTH);

	modelStack.Translate(0, 0, 0.001f);
	for (int ccount = 0; ccount < tileMap->getNumOfTilesWidth(); ++ccount)
	{
		for (int rcount = 0; rcount < tileMap->getNumOfTilesHeight(); ++rcount)
		{
			modelStack.PushMatrix(); 
			modelStack.Translate(ccount, rcount, 0.1f);

			if ( tileMap->getTile(ccount, rcount) == model->getSpawnPointID() )
			{
				model->setNewPlayerPos(ccount, rcount,-0.8f);
			}
			else if ( tileMap->getTile(ccount, rcount) == model->getExitPointID() )
			{
				model->setNewExitPos(ccount,rcount,0);
			}
			else if ( tileMap->getTile(ccount, rcount) == model->getEnemySpawnID() )
			{
				model->setNewEnemy(ccount,rcount,0,1);
			}
			else
			{
				RenderMesh(model->getTileMesh(), false, 6 * tileMap->getTile(ccount, rcount), 6);
			}
			modelStack.PopMatrix();
		}
	}
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

	glEnable(GL_DEPTH);
}

#undef reartileMap

void GameView2D::RenderPlayerCharacter()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);
	float ANGLE = Math::RadianToDegree(atan2(model->getPos().y - CCharacter_Player::GetInstance()->getPosition().y, model->getPos().x - CCharacter_Player::GetInstance()->getPosition().x));
	modelStack.Translate(0, 0, 1);
	modelStack.PushMatrix(); {
		modelStack.Translate(CCharacter_Player::GetInstance()->getPosition());
		modelStack.Translate(0.5, 0.5, 0);
		modelStack.Rotate(ANGLE,0,0,1);
		RenderMesh(model->getPlayerMesh(model->PISTOL_IDLE), false, 6 * CCharacter_Player::GetInstance()->getSpriteID(), 6 );
	} modelStack.PopMatrix();
}

#define mobsList model->getEnemyList()

void GameView2D::RenderMobs()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);

	float mapOffset_x, mapOffset_y;
	model->getOffset(mapOffset_x, mapOffset_y);

	for (int count = 0; count < mobsList.size(); ++count)
	{
		if (mobsList[count]->getActive())
		{
			modelStack.PushMatrix(); {
				modelStack.Translate(-mapOffset_x, -mapOffset_y, 1);
				modelStack.Translate(mobsList[count]->getPosition());
				//modelStack.Translate(0.5, 0.5, 0);
				RenderMesh(model->getTileMesh(), false, 6 * mobsList[count]->getSpriteID(), 6);
			} modelStack.PopMatrix();
		}
	}
}

#undef mobsList

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

void GameView2D::RenderGO(GameObject *go)
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
	}
}