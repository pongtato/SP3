#ifndef GAMEVIEW2D_H

#define GAMEVIEW2D_H

#include "View.h"
#include "GameModel2D.h"
#include "HighScore.h"
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
	void RenderScore();
	void RenderCountDownTimer();
	void RenderCountDownTimerIcon();
	void RenderPlayerDetectStatus();
	void RenderUI();
	void RenderCrosshair();
	void RenderKeysIcon();
	void RenderKeys();
	void RenderGO(GameObject *go, TileMap* tileMap);
	void RenderScene();
	void RenderHelpText();
	void RenderHealth();
	void RenderHDying();
	void RenderHBar();
	void RenderShotgunIcon();
	void RenderPistolIcon();
	void RenderRifleIcon();
	void RenderShotgunAmmo();
	void RenderPistolAmmo();
	void RenderRifleAmmo();
	void RenderLockPick();
	void RenderLockBar();
	void RenderLockBall();
	void RenderPrompt();
	void RenderExit();
	void RenderFog();
	void RenderPACount();
	void RenderRACount();
	void RenderSACount();
	void RenderPlayerRadius();
	void RenderHighScore();
};

#endif