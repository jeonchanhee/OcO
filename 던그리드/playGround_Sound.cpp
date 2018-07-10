#include "stdafx.h"
#include "playGround.h"

HRESULT playGround::Sound_init(void)
{
	SOUNDMANAGER->addSound("intro", "sound/back/intro.wav", true, false);
	SOUNDMANAGER->addSound("title", "sound/back/title.wav", true, true);
	SOUNDMANAGER->addSound("town", "sound/back/town.wav", true, true);

	return S_OK;
}