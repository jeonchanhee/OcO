#pragma once
#include "dungeonScene.h"
class dungeon4Scene : public dungeonScene
{
public:
	dungeon4Scene();
	~dungeon4Scene();
	HRESULT init();
	void update();
	void render();
	void setMonster();
};

