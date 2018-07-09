#pragma once
#include "dungeonScene.h"

class dungeon2Scene : public dungeonScene
{
private:
	
public:
	dungeon2Scene();
	~dungeon2Scene();

	HRESULT init();
	void setRandMapNum();
	void doorInit();

	void update();

	void setMonster();
};

