
#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <iostream>
#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib")

using namespace irrklang;

class CSoundManager
{
	
public:
	ISoundEngine* engine;

	CSoundManager(void);
	~CSoundManager(void);

	//Main Menu
	void mainMenuBGM();
	void ConfirmSound();
	void SelectSound();

	//Level BGMs
	void level1BGM();
	void level2BGM();
	void level3BGM();
	void level4BGM();

	//Player & Enemies
	void walkfloor();
	void walkMetal();
	void guardDie();

	//Guns
	void reloadSound();
	void pistolShot();
	void rifleShot();
	void shotgunShot();
	void emptyClip();

	//Player interactions
	void interactionSound();
	void alarmSound();
	void openDoorSound();
	void closeDoorSound();


	//Others
	void lasers();
};

#endif

