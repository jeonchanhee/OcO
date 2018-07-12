#pragma once
#include "dungeonScene.h"
class dungeon3Scene :
	public dungeonScene
{
public:
	dungeon3Scene();
	~dungeon3Scene();

	HRESULT init();
	void update();
	void render();
	void setMonster();
};

