#include "stdafx.h"
#include "playGround.h"

HRESULT playGround::Sound_init(void)
{
	SOUNDMANAGER->addSound("intro", "sound/back/intro.wav", true, false);
	SOUNDMANAGER->addSound("title", "sound/back/title.wav", true, true);
	SOUNDMANAGER->addSound("town", "sound/back/town.wav", true, true);
	SOUNDMANAGER->addSound("boss", "sound/back/boss.wav", true, true); //보스방에 있는동안





	//====================   PLAYER =================================


	//==================== ENEMY =================================
	SOUNDMANAGER->addSound("bat", "sound/enemy/bat.wav", false, false);
	SOUNDMANAGER->addSound("bat2", "sound/enemy/bat2.wav", false, false);
	SOUNDMANAGER->addSound("bat3", "sound/enemy/bat3.wav", false, false);
	SOUNDMANAGER->addSound("batFire", "sound/enemy/batFire.wav", false, false);
	SOUNDMANAGER->addSound("bossChest", "sound/enemy/bosschest.wav", false, false); //3층올라가자마자 나오는 소리
 	SOUNDMANAGER->addSound("bossLaughter", "sound/enemy/bossLaughter.wav", false, false); //보스있는곳 들어가면 나오는 소리
	SOUNDMANAGER->addSound("dropBomb", "sound/enemy/dropBomb.wav", false, false);
	SOUNDMANAGER->addSound("enemySound", "sound/enemy/enemySound.wav", false, false);
	SOUNDMANAGER->addSound("fairy", "sound/enemy/fairy.wav", false, false);
	SOUNDMANAGER->addSound("fireBullet", "sound/enemy/fireBullet.wav", false, false);
	SOUNDMANAGER->addSound("growl", "sound/enemy/growl.wav", false, false);
	SOUNDMANAGER->addSound("mosterDie", "sound/enemy/mosterDie.wav", false, false);
	SOUNDMANAGER->addSound("musicAngel", "sound/enemy/musicAngel.wav", false, false); //음표요정 공격소리
	SOUNDMANAGER->addSound("spawnMonster", "sound/enemy/spawnMonster.wav", false, false);
	SOUNDMANAGER->addSound("음악요정공격", "sound/enemy/음악요정공격.wav", false, false);
	SOUNDMANAGER->addSound("hitMonster", "sound/effect/hitMonster.wav", false, false); //몬스터 맞을 때 소리



	return S_OK;
}