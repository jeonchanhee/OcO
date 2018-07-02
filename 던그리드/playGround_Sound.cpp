#include "stdafx.h"
#include "playGround.h"

HRESULT playGround::Sound_init(void)
{
	SOUNDMANAGER->addSound("title", "sound/01_title.mp3", true, false);

	return S_OK;
}