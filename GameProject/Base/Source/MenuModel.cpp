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

	commands = new bool[NUM_COMMANDS];
	for (int count = 0; count < NUM_COMMANDS; ++count)
		commands[count] = false;
}

void MenuModel::Update(double dt)
{
	Model::Update(dt);

	if (commands[MOVE_UP]) arrowPosition = 0;
	else if (commands[MOVE_DOWN]) arrowPosition = 1;
	if (commands[ENTER]) throw arrowPosition;

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

int MenuModel::getArrowPosition()
{
	return arrowPosition;
}