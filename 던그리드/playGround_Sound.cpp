#include "stdafx.h"
#include "playGround.h"

HRESULT playGround::Sound_init(void)
{
	SOUNDMANAGER->addSound("intro", "sound/back/intro.wav", true, false);
	SOUNDMANAGER->addSound("title", "sound/back/title.wav", true, true);
	SOUNDMANAGER->addSound("town", "sound/back/town.wav", true, true);

	//====================   PLAYER =================================
	SOUNDMANAGER->addSound("칼사운드", "sound/player/검.wav", false, false);
	SOUNDMANAGER->addSound("대시사운드", "sound/player/dash.wav", false, false);
	SOUNDMANAGER->addSound("점프사운드", "sound/player/Jump.wav", false, false);
	SOUNDMANAGER->addSound("뒤짐사운드", "sound/player/dead.wav", false, false);
	
	return S_OK;
}