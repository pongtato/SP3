
#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <iostream>
#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib")

using namespace irrklang;

class CSoundManager
{
	ISoundEngine* engine;
public:
	CSoundManager(void);
	~CSoundManager(void);

	//sound functions here
	bool backgroundMusic();
	bool ConfirmSound();
	bool SelectSound();
};

#endif

