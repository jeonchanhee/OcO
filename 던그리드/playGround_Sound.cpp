#include "stdafx.h"
#include "playGround.h"

HRESULT playGround::Sound_init(void)
{
	SOUNDMANAGER->addSound("intro", "sound/back/intro.mp3", true, false);

	return S_OK;
}