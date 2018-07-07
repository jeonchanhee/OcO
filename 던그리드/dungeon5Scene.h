#pragma once
#include "dungeonScene.h"
class dungeon5Scene :
	public dungeonScene
{
public:
	dungeon5Scene();
	~dungeon5Scene();
	HRESULT init();
	void update();
	void setMonster();
};

