#ifndef GAMEMODELLEVEL4_H
#define GAMEMODELLEVEL4_H

#include "GameModel2D.h"

#include "MouseCharacter.h"

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
