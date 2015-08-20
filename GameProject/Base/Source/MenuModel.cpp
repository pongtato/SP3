#include "MenuModel.h"

#include "MeshBuilder.h"
#include "LoadTGA.h"

MenuModel::MenuModel()
{
	Sound.mainMenuBGM();
}

MenuModel::~MenuModel()
{
}

void MenuModel::Init()
{

	Model::Init();

	menuScreen = MeshBuilder::GenerateQuad("menu", Color());
	menuScreen->textureID[0] = LoadTGA("Image//Menu//BG.tga");
	arrow = MeshBuilder::GenerateQuad("arrow", Color());
	arrow->textureID[0] = LoadTGA("Image//TempPointer.tga");
	choice = MeshBuilder::GenerateQuad("choice", Color());
	choice->textureID[0] = LoadTGA("Image//MenuChoice.tga");

	startBtn = MeshBuilder::GenerateQuad("startBtn", Color());
	startBtn->textureID[0] = LoadTGA("Image//Menu//Start.tga");
	settingsBtn = MeshBuilder::GenerateQuad("settingsBtn", Color());
	settingsBtn->textureID[0] = LoadTGA("Image//Menu//Settings.tga");
	exitBtn = MeshBuilder::GenerateQuad("exitBtn", Color());
	exitBtn->textureID[0] = LoadTGA("Image//Menu//Exit.tga");

	Lv1 = MeshBuilder::GenerateQuad("Lv1", Color());
	Lv1->textureID[0] = LoadTGA("Image//Menu//lv1.tga");
	Lv2 = MeshBuilder::GenerateQuad("Lv2", Color());
	Lv2->textureID[0] = LoadTGA("Image//Menu//lv2.tga");
	Lv3 = MeshBuilder::GenerateQuad("Lv3", Color());
	Lv3->textureID[0] = LoadTGA("Image//Menu//lv3.tga");
	Lv4 = MeshBuilder::GenerateQuad("Lv4", Color());
	Lv4->textureID[0] = LoadTGA("Image//Menu//lv4.tga");

	arrowPosition = 0;
	menuTimer = false;
	SelectingLevels = false;

	commands = new bool[NUM_COMMANDS];
	for (int count = 0; count < NUM_COMMANDS; ++count)
		commands[count] = false;

}

void MenuModel::Update(double dt)
{
	Model::Update(dt);
	if (!menuTimer)
	{
		if (commands[MOVE_UP])
		{
			Sound.SelectSound();
			if ( !SelectingLevels )
			{
				arrowPosition = Math::Wrap(arrowPosition -= 1,0,2);
			}
			else
			{
				arrowPosition = Math::Wrap(arrowPosition -= 1,0,3);
			}
			menuTimer = true;
		}
		else if (commands[MOVE_DOWN]) 
		{ 
			Sound.SelectSound();
			if ( !SelectingLevels )
			{
				arrowPosition = Math::Wrap(arrowPosition += 1,0,2);
			}
			else
			{
				arrowPosition = Math::Wrap(arrowPosition += 1,0,3);
			}
			menuTimer = true;
		}
		if (commands[ENTER])
		{
			Sound.ConfirmSound();
			if ( SelectingLevels)
			{
				Sound.engine->stopAllSounds();
				throw arrowPosition;
			}
			else if ( arrowPosition == 0 && !SelectingLevels)
			{
				SelectingLevels = true;
				menuTimer = true;
			}
		}
	}

	if ( !SelectingLevels )
	{
		switch ( arrowPosition )
		{
		case 0:
			{
				startBtn->textureID[0] = LoadTGA("Image//Menu//Start_H.tga");
				settingsBtn->textureID[0] = LoadTGA("Image//Menu//Settings.tga");
				exitBtn->textureID[0] = LoadTGA("Image//Menu//Exit.tga");
			}
			break;
		case 1:
			{
				startBtn->textureID[0] = LoadTGA("Image//Menu//Start.tga");
				settingsBtn->textureID[0] = LoadTGA("Image//Menu//Settings_H.tga");
				exitBtn->textureID[0] = LoadTGA("Image//Menu//Exit.tga");
			}
			break;
		case 2:
			{
				startBtn->textureID[0] = LoadTGA("Image//Menu//Start.tga");
				settingsBtn->textureID[0] = LoadTGA("Image//Menu//Settings.tga");
				exitBtn->textureID[0] = LoadTGA("Image//Menu//Exit_H.tga");
			}
			break;
		case 3:
			{
				startBtn->textureID[0] = LoadTGA("Image//Menu//Start.tga");
				settingsBtn->textureID[0] = LoadTGA("Image//Menu//Settings.tga");
				exitBtn->textureID[0] = LoadTGA("Image//Menu//Exit_H.tga");
			}
			break;
		}
	}
	else if ( SelectingLevels )
	{
		switch ( arrowPosition )
		{
		case 0:
			{
				Lv1->textureID[0] = LoadTGA("Image//Menu//lv1_H.tga");
				Lv2->textureID[0] = LoadTGA("Image//Menu//lv2.tga");
				Lv3->textureID[0] = LoadTGA("Image//Menu//lv3.tga");
				Lv4->textureID[0] = LoadTGA("Image//Menu//lv4.tga");
			}
			break;
		case 1:
			{
				Lv1->textureID[0] = LoadTGA("Image//Menu//lv1.tga");
				Lv2->textureID[0] = LoadTGA("Image//Menu//lv2_H.tga");
				Lv3->textureID[0] = LoadTGA("Image//Menu//lv3.tga");
				Lv4->textureID[0] = LoadTGA("Image//Menu//lv4.tga");
			}
			break;
		case 2:
			{
				Lv1->textureID[0] = LoadTGA("Image//Menu//lv1.tga");
				Lv2->textureID[0] = LoadTGA("Image//Menu//lv2.tga");
				Lv3->textureID[0] = LoadTGA("Image//Menu//lv3_H.tga");
				Lv4->textureID[0] = LoadTGA("Image//Menu//lv4.tga");
			}
			break;
		case 3:
			{
				Lv1->textureID[0] = LoadTGA("Image//Menu//lv1.tga");
				Lv2->textureID[0] = LoadTGA("Image//Menu//lv2.tga");
				Lv3->textureID[0] = LoadTGA("Image//Menu//lv3.tga");
				Lv4->textureID[0] = LoadTGA("Image//Menu//lv4_H.tga");
			}
			break;
		}
	}

	if (!commands[ENTER] && !commands[MOVE_UP] && !commands[MOVE_DOWN])
	{
		menuTimer = false;
	}
	for (int count = 0; count < NUM_COMMANDS; ++count)
		commands[count] = false;
}

void MenuModel::setCommands(int command)
{
	if (command >= 0 && command < NUM_COMMANDS)
		commands[command] = true;
}

Mesh* MenuModel::getMenuMesh()
{
	return menuScreen;
}

Mesh* MenuModel::getArrowMesh()
{
	return arrow;
}

Mesh* MenuModel::getChoiceMesh()
{
	return choice;
}

Mesh* MenuModel::getstartBtn()
{
	return startBtn;
}

Mesh* MenuModel::getsettingsBtn()
{
	return settingsBtn;
}

Mesh* MenuModel::getexitBtn()
{
	return exitBtn;
}

Mesh* MenuModel::getLv1()
{
	return Lv1;
}


Mesh* MenuModel::getLv2()
{
	return Lv2;
}

Mesh* MenuModel::getLv3()
{
	return Lv3;
}

Mesh* MenuModel::getLv4()
{
	return Lv4;
}

int MenuModel::getArrowPosition()
{
	return arrowPosition;
}

bool MenuModel::getIsSelectingLevels()
{
	return SelectingLevels;
}