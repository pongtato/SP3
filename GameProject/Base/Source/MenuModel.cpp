#include "MenuModel.h"

#include "MeshBuilder.h"
#include "LoadTGA.h"

MenuModel::MenuModel()
{
}

MenuModel::~MenuModel()
{
}

void MenuModel::Init()
{
	Model::Init();

	menuScreen = MeshBuilder::GenerateQuad("menu", Color());
	menuScreen->textureID[0] = LoadTGA("Image//SP3_Background.tga");
	arrow = MeshBuilder::GenerateQuad("arrow", Color());
	arrow->textureID[0] = LoadTGA("Image//TempPointer.tga");
	choice = MeshBuilder::GenerateQuad("choice", Color());
	choice->textureID[0] = LoadTGA("Image//MenuChoice.tga");

	arrowPosition = 0;
	menuTimer = false;

	commands = new bool[NUM_COMMANDS];
	for (int count = 0; count < NUM_COMMANDS; ++count)
		commands[count] = false;
}

void MenuModel::Update(double dt)
{
	Model::Update(dt);
	if (!menuTimer)
	{
		if (commands[MOVE_UP] && arrowPosition >= 0)
		{
			arrowPosition--;
			menuTimer = true;
		}
		else if (commands[MOVE_DOWN] && arrowPosition < 2) 
		{ 
			arrowPosition++;
			menuTimer = true;
		}
		if (commands[ENTER])
		{
			throw arrowPosition;
			menuTimer = true;
		}
	}

	if (!commands[ENTER] && !commands[MOVE_UP] && !commands[MOVE_DOWN])
	{
		menuTimer = false;
	}
	for (int count = 0; count < NUM_COMMANDS; ++count)
		commands[count] = false;
	std::cout << menuTimer  << " " << arrowPosition << std::endl;
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

int MenuModel::getArrowPosition()
{
	return arrowPosition;
}