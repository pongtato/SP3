#ifndef MENUMODEL_H
#define MENUMODEL_H

#include "Model.h"
#include "SoundManager.h"

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
	Mesh *menuScreen;
	Mesh *arrow;
	Mesh *choice;
	Mesh *startBtn;
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
	Mesh* getexitBtn();

	Mesh* getLv1();
	Mesh* getLv2();
	Mesh* getLv3();
	Mesh* getLv4();
	int getArrowPosition();
	bool getIsSelectingLevels();

	CSoundManager Sound;
};

#endif