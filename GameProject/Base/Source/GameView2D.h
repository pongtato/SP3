#ifndef GAMEVIEW2D_H

#define GAMEVIEW2D_H

#include "View.h"
#include "GameModel2D.h"
#include "TileMap.h"

class GameView2D : public View
{
protected:
	View* view;
private:

public:
	GameView2D(Model* model = NULL);

	void Render();
	void RenderBackground();
	void RenderTileMap();
	void RenderRearTileMap();
	void RenderPlayerCharacter();
	void RenderMobs();
	void RenderMobsDetection();
	void RenderCountDownTimer();
	void RenderUI();
	void RenderCrosshair();
	void RenderGO(GameObject *go, TileMap* tileMap);
	void RenderScene();
	void RenderHelpText();
	void RenderHealth();
	void RenderHBar();
	void RenderLockPick();
	void RenderLockBar();
	void RenderLockBall();
};

#endif