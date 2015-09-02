
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

//main menu
void CSoundManager::mainMenuBGM()
{
	//play main song
	ISound* music = engine->play2D("../irrKlang/media/mainMenuBGM.mp3",
		true, false, true);

	engine->setSoundVolume(0.25f);
}
void CSoundManager::ConfirmSound()
{
	//main menu confirming choice sound
	ISound* music = engine->play2D("../irrKlang/media/confirm.wav",
		false, false, true);

	//engine->setSoundVolume(2.f);
}
void CSoundManager::SelectSound()
{
	//main menu selecting choice sound
	ISound* music = engine->play2D("../irrKlang/media/select.wav",
		false, false, true);

	//engine->setSoundVolume(2.f);
}

//background musics
void CSoundManager::level1BGM()
{
	//Level 1 background music
	ISound* music = engine->play2D("../irrKlang/media/Level1BGM.mp3",
		true, false, true);

	engine->setSoundVolume(0.5f);
}
void CSoundManager::level2BGM()
{
	//Level 2 background music
	ISound* music = engine->play2D("../irrKlang/media/Level2BGM.mp3",
		true, false, true);

	//engine->setSoundVolume(0.5f);

}
void CSoundManager::level3BGM()
{
	//Level 3 background music
	ISound* music = engine->play2D("../irrKlang/media/Level3BGM2.mp3",
		true, false, true);

	//engine->setSoundVolume(0.25f);
}
void CSoundManager::level4BGM()
{
	//Level 4 background music
	ISound* music = engine->play2D("../irrKlang/media/Level4BGM.mp3",
		true, false, true);

	//engine->setSoundVolume(0.5f);
}

//Player & Enemies
void CSoundManager::walkfloor()
{
	//player walking on the floor/concrete
	ISound* music = engine->play2D("../irrKlang/media/walkOnConcrete.wav",
		false, false, false);

	//engine->setSoundVolume(0.4f);
}
void CSoundManager::walkMetal()
{
	//player walking on metal
	ISound* music = engine->play2D("../irrKlang/media/walkOnMetal.wav",
		false, false, true);

	//engine->setSoundVolume(0.4f);
}
void CSoundManager::guardAlert()
{
	//player alerted the alarm
	ISound* music = engine->play2D("../irrKlang/media/alert.mp3",
		false, false, false);

	engine->setSoundVolume(0.4f);
}

void CSoundManager::guardDie()
{
	//when the guards die
	ISound* music = engine->play2D("../irrKlang/media/guardDie.wav",
		false, false, true);

	engine->setSoundVolume(0.4f);
}

//Guns
void CSoundManager::reloadSound()
{
	//reloading gun
	ISound* music = engine->play2D("../irrKlang/media/reloadGun.mp3",
		false, false, true);

	engine->setSoundVolume(0.4f);
}
void CSoundManager::pistolShot()
{
	//firing a pistol
	ISound* music = engine->play2D("../irrKlang/media/pistolSilent.wav",
		false, false, true);

	engine->setSoundVolume(0.4f);
}
void CSoundManager::rifleShot()
{
	//firing a rifle
	ISound* music = engine->play2D("../irrKlang/media/rifleShot.mp3",
		false, false, true);

	engine->setSoundVolume(0.4f);
}
void CSoundManager::shotgunShot()
{
	//firing a shotgun
	ISound* music = engine->play2D("../irrKlang/media/shotgunShot.wav",
		false, false, true);

	engine->setSoundVolume(0.4f);
}
void CSoundManager::emptyClip()
{
	//firing an empty clip
	ISound* music = engine->play2D("../irrKlang/media/dryfiring.wav", 
		false, false, true);

	//engine->setSoundVolume(0.4f);
}
//Player interactions
void CSoundManager::interactionSound()
{
	//when a notifcation or help message pops up
	ISound* music = engine->play2D("../irrKlang/media/popup.wav",
		false, false, true);

	engine->setSoundVolume(0.4f);
}
void CSoundManager::alarmSound()
{
	//alarm sound when being found out
	ISound* music = engine->play2D("../irrKlang/media/alarmTriggered.wav",
		false, false, true);

	engine->setSoundVolume(0.4f);
}
void CSoundManager::openDoorSound()
{
	//opening door
	ISound* music = engine->play2D("../irrKlang/media/openDoor.wav",
		false, false, true);

	engine->setSoundVolume(0.4f);
}
void CSoundManager::closeDoorSound()
{
	//close door
	ISound* music = engine->play2D("../irrKlang/media/closeDoor.wav",
		false, false, true);

	engine->setSoundVolume(0.4f);
}
void CSoundManager::PCON()
{
	//sound when hacking into pc
	ISound* music = engine->play2D("../irrKlang/media/pcon.wav",
		false, false, true);

	engine->setSoundVolume(0.4f);
}

//Others
void CSoundManager::lasers()
{
	//sound before laser is disabled
	ISound* music = engine->play2D("../irrKlang/media/substainedLaser.wav",
		false, false, true);

	engine->setSoundVolume(0.4f);
}