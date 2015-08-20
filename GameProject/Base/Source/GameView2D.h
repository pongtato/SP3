#ifndef GAMEVIEW2D_H

#define GAMEVIEW2D_H

#include "View.h"
#include "GameModel2D.h"

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
	void RenderScore();
	void RenderCrosshair();
	void RenderGO(GameObject *go);

};

#endif