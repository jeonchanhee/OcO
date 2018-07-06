#pragma once
#include "dungeonScene.h"
class dungeon8Scene :
	public dungeonScene
{
public:
	dungeon8Scene();
	~dungeon8Scene();
	HRESULT init();
	void update();
};

