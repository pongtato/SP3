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

	modelStack.PushMatrix(); {
		//RenderBackground();
		RenderMobs();
		RenderRearTileMap();
		RenderTileMap();
		RenderPlayerCharacter();
		RenderCrosshair();
		//RenderScore();
	} modelStack.PopMatrix();
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
			RenderMesh(model->getTileMesh(), false, 6 * tileMap->getTile(ccount, rcount), 6);
			modelStack.PopMatrix();

			if ( tileMap->getTile(ccount, rcount) == model->getSpawnPointID() )
			{
				model->setNewPlayerPos(ccount, rcount,-0.8f);
			}
			if ( tileMap->getTile(ccount, rcount) == model->getExitPointID() )
			{
				model->setNewExitPos(ccount,rcount,0);
			}
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

#define player model->getPlayer()

void GameView2D::RenderPlayerCharacter()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);

	modelStack.Translate(0, 0, 1);
	modelStack.PushMatrix(); {
		modelStack.Translate(player->getPosition());
		modelStack.Translate(0.5, 0.5, 0);

		RenderMesh(model->getPlayerMesh(), false, 6 * player->getSpriteState(), 6);
	} modelStack.PopMatrix();
}

#undef player

#define mobsList model->getGuardsList()

void GameView2D::RenderMobs()
{
	GameModel2D* model = dynamic_cast<GameModel2D *>(m_model);

	float mapOffset_x, mapOffset_y;
	model->getOffset(mapOffset_x, mapOffset_y);

	for (int count = 0; count < mobsList.size(); ++count)
	{
		if (mobsList[count]->isActive())
		{
			modelStack.PushMatrix(); {
				modelStack.Translate(-mapOffset_x, -mapOffset_y, 1);
				modelStack.Translate(mobsList[count]->getPosition());
				modelStack.Translate(0.5, 0.5, 0);

				RenderMesh(model->getMobsMesh(), false, 6 * mobsList[count]->getSpriteState(), 6);
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
