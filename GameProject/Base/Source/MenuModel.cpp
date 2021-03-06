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
	loadBtn = MeshBuilder::GenerateQuad("loadBtn", Color());
	loadBtn->textureID[0] = LoadTGA("Image//Menu//Load.tga");
	creditsBtn = MeshBuilder::GenerateQuad("creditsBtn", Color());
	creditsBtn->textureID[0] = LoadTGA("Image//Menu//Credits.tga");
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
	Text = MeshBuilder::GenerateText("text", 16, 16);
	Text->textureID[0] = LoadTGA("Image//Font.tga");
	arrowPosition = 0;

	menuTimer = false;
	SelectingLevels = false;
	m_credits = false;

	commands = new bool[NUM_COMMANDS];
	for (int count = 0; count < NUM_COMMANDS; ++count)
		commands[count] = false;

	Readx = 0;
	Ready = 0;
	Readz = 0;

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
				arrowPosition = Math::Wrap(arrowPosition -= 1,0,3);
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
				arrowPosition = Math::Wrap(arrowPosition += 1,0,3);
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

			if ( m_credits )
			{
				m_credits = false;
				menuScreen->textureID[0] = LoadTGA("Image//Menu//BG.tga");
				menuTimer = true;
				return;
			}

			if ( SelectingLevels)
			{
				Sound.engine->stopAllSounds();
				Sound.ConfirmSound();
				throw arrowPosition;
			}
			else if ( arrowPosition == 0 && !SelectingLevels)
			{
				SelectingLevels = true;
				menuTimer = true;
			}
			else if (arrowPosition == 1 && !SelectingLevels)
			{
				//load last save
				string line;
				ifstream playerPos("savepoint.txt");

				if (playerPos.is_open())
				{
					string aLineOfText = "";
					string token = "";

					vector<string> data;
					data.clear();

					getline( playerPos, aLineOfText );
					//aLineOfText.erase(aLineOfText.find(' '),1);
					istringstream iss( aLineOfText );

					while ( getline( iss, token, ',' ) || getline( iss, token, '/' ))
						data.push_back( token );

					if ( data[0] != "" )
					{ 
						CCharacter_Player::GetInstance()->LoadedPosition.Set(stof(data[0].c_str()), stof(data[1].c_str()), stof(data[2].c_str()));
						CCharacter_Player::GetInstance()->LoadingGame = true;
						CCharacter_Player::GetInstance()->LoadedTime = atoi(data[3].c_str());
						CCharacter_Player::GetInstance()->LoadedHighScore = atoi(data[4].c_str());
						throw atoi(data[5].c_str());
					}
				}
				else
				{
					cout << "unable to open file";
				}
			}
			else if ( arrowPosition == 2 && !SelectingLevels && !m_credits)
			{
				m_credits = true;
				menuScreen->textureID[0] = LoadTGA("Image//Menu//BGCREDITS.tga");
				menuTimer = true;
			}
			else if (arrowPosition == 3 && !SelectingLevels)
			{
				exit(0);
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
				//settingsBtn->textureID[0] = LoadTGA("Image//Menu//Settings.tga");
				loadBtn->textureID[0] = LoadTGA("Image//Menu//Load.tga");
				creditsBtn->textureID[0] = LoadTGA("Image//Menu//Credits.tga");
				exitBtn->textureID[0] = LoadTGA("Image//Menu//Exit.tga");
			}
			break;

		case 1:
			{
				startBtn->textureID[0] = LoadTGA("Image//Menu//Start.tga");
				//settingsBtn->textureID[0] = LoadTGA("Image//Menu//Settings_H.tga");
				loadBtn->textureID[0] = LoadTGA("Image//Menu//Load_H.tga");
				creditsBtn->textureID[0] = LoadTGA("Image//Menu//Credits.tga");
				exitBtn->textureID[0] = LoadTGA("Image//Menu//Exit.tga");
			}
			break;
		case 2:
			{
				startBtn->textureID[0] = LoadTGA("Image//Menu//Start.tga");
				//settingsBtn->textureID[0] = LoadTGA("Image//Menu//Settings.tga");
				loadBtn->textureID[0] = LoadTGA("Image//Menu//Load.tga");
				creditsBtn->textureID[0] = LoadTGA("Image//Menu//Credits_H.tga");
				exitBtn->textureID[0] = LoadTGA("Image//Menu//Exit.tga");
			}
			break;
		case 3:
			{
				startBtn->textureID[0] = LoadTGA("Image//Menu//Start.tga");
				//settingsBtn->textureID[0] = LoadTGA("Image//Menu//Settings.tga");
				loadBtn->textureID[0] = LoadTGA("Image//Menu//Load.tga");
				creditsBtn->textureID[0] = LoadTGA("Image//Menu//Credits.tga");
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

Mesh* MenuModel::getTextMesh()
{
	return Text;
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

Mesh* MenuModel::getloadBtn()
{
	return loadBtn;
}

Mesh* MenuModel::getcreditsBtn()
{
	return creditsBtn;
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