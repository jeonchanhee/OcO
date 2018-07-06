#pragma once
#include "dungeonScene.h"
class dungeon1Scene : public dungeonScene
{

public:
	dungeon1Scene();
	~dungeon1Scene();

	HRESULT init();
	void update();
	/*void render();
	void release();*/
};

