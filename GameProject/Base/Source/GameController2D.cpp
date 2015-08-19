#include "GameController2D.h"

GameController2D::GameController2D(Model* model, View* view) : Controller(model, view)
{
}

GameController2D::~GameController2D()
{
}

void GameController2D::Update()
{
	if (IsKeyPressed('W'))
		model->setCommands(GameModel2D::COMMANDS::MOVE_UP);
	if (IsKeyPressed('A'))
		model->setCommands(GameModel2D::COMMANDS::MOVE_LEFT);
	if (IsKeyPressed('S'))
		model->setCommands(GameModel2D::COMMANDS::MOVE_DOWN);
	if (IsKeyPressed('D'))
		model->setCommands(GameModel2D::COMMANDS::MOVE_RIGHT);
	if (IsKeyPressed(VK_SPACE))
		model->setCommands(GameModel2D::COMMANDS::JUMP);
	if (IsKeyPressed(VK_RETURN))
		model->setCommands(GameModel2D::COMMANDS::ENTER);
	//Weapon changing
	if (IsKeyPressed('Q'))
		model->setCommands(GameModel2D::COMMANDS::PREVWEAP);
	if (IsKeyPressed('E'))
		model->setCommands(GameModel2D::COMMANDS::NEXTWEAP);
	Controller::Update();
	
}