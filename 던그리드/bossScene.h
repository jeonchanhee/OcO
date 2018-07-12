#pragma once
#include "dungeonScene.h"

class Player;

class bossScene : public dungeonScene
{
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
};

