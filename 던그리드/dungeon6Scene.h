#pragma once
#include "dungeonScene.h"
class dungeon6Scene :
	public dungeonScene
{
public:
	dungeon6Scene();
	~dungeon6Scene();
	HRESULT init();
	void update();
	void render();
	void setRandMapNum();
	void doorInit();
	void setMonster();
};

