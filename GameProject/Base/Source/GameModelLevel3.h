#ifndef GAMEMODELLEVEL3_H
#define GAMEMODELLEVEL3_H

#include "GameModel2D.h"

#include "MouseCharacter.h"

class GameModelLevel3 : public GameModel2D
{
private:

public:
	GameModelLevel3();
	~GameModelLevel3();

	void Init();
	void Update(double dt);
};

#endif
