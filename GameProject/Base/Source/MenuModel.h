#ifndef MENUMODEL_H
#define MENUMODEL_H

#include "Model.h"
#include "SoundManager.h"
#include "GameView2D.h"

class MenuModel : public Model
{
public:
	enum COMMANDS {
		MOVE_UP,
		MOVE_DOWN,
		ENTER,
		NUM_COMMANDS,
	};

private:
	Mesh *Text;
	Mesh *menuScreen;
	Mesh *arrow;
	Mesh *choice;
	Mesh *startBtn;
	Mesh *loadBtn;
	Mesh *creditsBtn;
	Mesh *settingsBtn;
	Mesh *exitBtn;

	Mesh *Lv1;
	Mesh *Lv2;
	Mesh *Lv3;
	Mesh *Lv4;

	int arrowPosition;
	bool menuTimer;
	bool SelectingLevels;

public:
	MenuModel();
	~MenuModel();

	void Init();
	void Update(double dt);
	void setCommands(int command);
	Mesh* getMenuMesh();
	Mesh* getArrowMesh();
	Mesh* getChoiceMesh();

	Mesh* getstartBtn();
	Mesh* getsettingsBtn();
	Mesh* getloadBtn();
	Mesh* getcreditsBtn();
	Mesh* getexitBtn();

	Mesh* getLv1();
	Mesh* getLv2();
	Mesh* getLv3();
	Mesh* getLv4();

	Mesh* getTextMesh();

	int getArrowPosition();
	bool getIsSelectingLevels();
	bool m_credits;

	CSoundManager Sound;
};

#endif