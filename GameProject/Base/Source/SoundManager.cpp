
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
	//play main song
	ISound* music = engine->play2D("../irrKlang/media/BillieJean.mp3",
		true, false, true);

	engine->setSoundVolume(0.25f);

	return true;
}

bool CSoundManager::ConfirmSound()
{
	//play main song
	ISound* music = engine->play2D("../irrKlang/media/confirm.wav",
		false, false, true);

	engine->setSoundVolume(0.25f);

	return true;
}

bool CSoundManager::SelectSound()
{
	//play main song
	ISound* music = engine->play2D("../irrKlang/media/select.wav",
		false, false, true);

	engine->setSoundVolume(0.25f);

	return true;
}