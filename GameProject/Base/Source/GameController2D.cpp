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
		model->setCommands(GameModel2D::COMMANDS::UNLOCK);
	if (IsKeyPressed(VK_RETURN))
		model->setCommands(GameModel2D::COMMANDS::ENTER);
	if (IsKeyPressed(VK_ESCAPE))
		model->setCommands(GameModel2D::COMMANDS::ESCAPE);
	//Weapon changing
	//if (IsKeyPressed('Q'))
	//	model->setCommands(GameModel2D::COMMANDS::PREVWEAP);
	//if (IsKeyPressed('E'))
	//	model->setCommands(GameModel2D::COMMANDS::NEXTWEAP);

	if (IsKeyPressed('1'))
		model->setCommands(GameModel2D::COMMANDS::WEAPON1);
	if (IsKeyPressed('2'))
		model->setCommands(GameModel2D::COMMANDS::WEAPON2);
	if (IsKeyPressed('3'))
		model->setCommands(GameModel2D::COMMANDS::WEAPON3);

	if (glfwGetMouseButton(view->getWindow(), 0))
		model->setCommands(GameModel2D::COMMANDS::SHOOT);
	if (IsKeyPressed('R'))
		model->setCommands(GameModel2D::COMMANDS::RELOAD);
	if (IsKeyPressed('X'))
		model->setCommands(GameModel2D::COMMANDS::CHECK);
	if (IsKeyPressed('E'))
		model->setCommands(GameModel2D::COMMANDS::INTERACT);
	Controller::Update();
	
}