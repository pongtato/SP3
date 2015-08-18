
#include "SoundManager.h"

CSoundManager::CSoundManager(void)
{
	engine = createIrrKlangDevice();
	engine->setDefault3DSoundMinDistance(2.0f);
	engine->setDefault3DSoundMaxDistance(5.0f);
}


CSoundManager::~CSoundManager(void)
{
	engine->drop();
}


bool CSoundManager::backgroundMusic()
{

	if (!engine)
		return false; // error starting up the engine

	if (engine)
		std::cout << "main Billie Jean sound played" << std::endl;
	//play main song
	ISound* music = engine->play2D("../irrKlang/media/BillieJean.mp3",
		true, false, true);


	engine->setSoundVolume(0.25f);


	return true;

}

