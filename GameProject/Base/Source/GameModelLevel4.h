#ifndef GAMEMODELLEVEL4_H
#define GAMEMODELLEVEL4_H

#include "GameModel2D.h"

#include "Character_Enemy.h"

class GameModelLevel4 : public GameModel2D
{
private:

public:
	GameModelLevel4();
	~GameModelLevel4();

	void Init();
	void Update(double dt);
};

#endif
