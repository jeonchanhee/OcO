#pragma once
#include "dungeonScene.h"



class dungeon1Scene : public dungeonScene
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
	dungeon1Scene();
	~dungeon1Scene();

	HRESULT init();
	void setRandMapNum();
	void doorInit();
	//void torchInit();
	//void portalInit();
	void setDungeonDoor();

	void update();
	void render();
};

