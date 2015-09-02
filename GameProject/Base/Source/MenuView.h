#ifndef MENUVIEW_H
#define MENUVIEW_H

#include "View.h"
#include "MenuModel.h"
#include "HighScore.h"
class MenuView : public View
{
private:


public:
	MenuView(Model* model = NULL);
	~MenuView();

	void Render();
	void RenderMenu();
	string getHighScore();
};

#endif