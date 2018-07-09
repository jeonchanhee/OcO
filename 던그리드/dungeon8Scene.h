#pragma once
#include "dungeonScene.h"


class dungeon8Scene : public dungeonScene
{
private:
	struct tagDungeonDoor
	{
		image* img;
		animation* ani;
		float x, y;
		int count;
	};

private:
	tagDungeonDoor _dungeonDoor;
public:
	dungeon8Scene();
	~dungeon8Scene();
	HRESULT init();
	void setRandMapNum();
	void doorInit();
	void setDungeonDoor();

	void update();

	void render();
	
	//void setMonster();
};

