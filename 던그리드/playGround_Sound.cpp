#include "stdafx.h"
#include "playGround.h"

HRESULT playGround::Sound_init(void)
{
	SOUNDMANAGER->addSound("intro", "sound/back/intro.wav", true, false);
	SOUNDMANAGER->addSound("title", "sound/back/title.wav", true, true);
	SOUNDMANAGER->addSound("town", "sound/back/town.wav", true, true);

	//====================   PLAYER =================================
	SOUNDMANAGER->addSound("Į����", "sound/player/��.wav", false, false);
	SOUNDMANAGER->addSound("��û���", "sound/player/dash.wav", false, false);
	SOUNDMANAGER->addSound("��������", "sound/player/Jump.wav", false, false);
	SOUNDMANAGER->addSound("��������", "sound/player/dead.wav", false, false);
	
	return S_OK;
}