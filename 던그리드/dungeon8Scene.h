#pragma once
#include "dungeonScene.h"

class RandomDungeon1;

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

	RECT _doorRc;
	RandomDungeon1* _randMap1;
	bool _enter;
	float _time;
public:
	dungeon8Scene();
	~dungeon8Scene();
	HRESULT init();
	void setRandMapNum();
	void doorInit();
	void setDungeonDoor();

	static void closeFunction(void * obj);

	void update();

	void render();
	
	//void setMonster();
};

