#include "GameModelLevel2.h"

GameModelLevel2::GameModelLevel2()
{
	Sound.level2BGM();
}

GameModelLevel2::~GameModelLevel2()
{
	delete m_tileMap;
	delete m_ReartileMap;
	delete m_AItilemap;
	GameModel2D::Exit();
}

void GameModelLevel2::Init()
{
	Model::Init();
	GameModel2D::Init();

	m_tileMap = new TileMap();
	m_tileMap->Init(32, 32, 32, 32, 32);
	m_tileMap->LoadMap("Image//Maps//L2_L2.csv");

	m_ReartileMap = new TileMap();
	m_ReartileMap->Init(32, 32, 32, 32, 32);
	m_ReartileMap->LoadMap("Image//Maps//L2_L1.csv");

	m_AItilemap = new TileMap();
	m_AItilemap->Init(32, 32, 32, 32, 32);
	m_AItilemap->LoadMap("Image//Maps//L2_AI.csv");

	CCharacter_Player::GetInstance()->Init(newPlayerPos.x - 0.5f,
			newPlayerPos.y - 0.25f,
			newPlayerPos.z,1,1,100,1,5);

	getMapData();
	m_CurrentLevel = 2;
}

void GameModelLevel2::Update(double dt)
{
	if ( SpawnReady )
	{
		CCharacter_Player::GetInstance()->Init(newPlayerPos.x,
			newPlayerPos.y,
			newPlayerPos.z,1,1,100,1,5);
		SpawnReady = false;
	}
	GameModel2D::Update(dt);
}
