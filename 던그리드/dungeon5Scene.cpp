#include "stdafx.h"
#include "dungeon5Scene.h"


dungeon5Scene::dungeon5Scene()
{
}


dungeon5Scene::~dungeon5Scene()
{
}

HRESULT dungeon5Scene::init()
{
	_isMapSet = true;
	chooseMap(6);
	selectSize(6);
	mapload();
	setCamera();

	load();

	_dungeonNum = 4;

	if (_randNum == 2)
	{
		_route.push_back(10);
		_route.push_back(6);
		_route.push_back(11);
	}
	if (_randNum == 4)
	{
		_route.push_back(1);
		_route.push_back(6);
		_route.push_back(10);
	}

	_door.resize(3);

	_door[0].x = (850 % 50) * TILESIZE, _door[0].y = (850 / 50) * TILESIZE;
	_door[1].x = (1375 % 50) * TILESIZE, _door[1].y = (1375 / 50) * TILESIZE;
	_door[2].x = (448 % 50) * TILESIZE, _door[2].y = (448 / 50) * TILESIZE;

	_door[0].rc = RectMake(_door[0].x, _door[0].y, TILESIZE, TILESIZE * 4);
	_door[2].rc = RectMake(_door[2].x, _door[2].y, TILESIZE, TILESIZE * 4);
	_door[1].rc = RectMake(_door[1].x, _door[1].y, TILESIZE * 4, TILESIZE);

	return S_OK;
}

void dungeon5Scene::update()
{
	nextTest();
}