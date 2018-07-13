#pragma once
#include "dungeonScene.h"
class dungeon7Scene :
	public dungeonScene
{
public:
	dungeon7Scene();
	~dungeon7Scene();
	HRESULT init();
	void doorInit();
	void update();
	void render();
	void setMonster();
};

