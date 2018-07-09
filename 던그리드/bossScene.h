#pragma once
#include "dungeonScene.h"
class bossScene : public dungeonScene
{
private:
	enum SWORDDIRECTION
	{
		SWORD_READY,
		SWORD_FALLING,
		SWORD_DOWN
	};
private:
	Bullet* _sword;
	int _swordCount;
public:
	bossScene();
	~bossScene();
	HRESULT init();
	void update();
	void render();
	void setBossMon();
	void bossSwordFire();
};

