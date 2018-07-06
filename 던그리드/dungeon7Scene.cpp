#include "stdafx.h"
#include "dungeon7Scene.h"


dungeon7Scene::dungeon7Scene()
{
}


dungeon7Scene::~dungeon7Scene()
{
}

HRESULT dungeon7Scene::init()
{
	_isMapSet = true;
	chooseMap(8);
	selectSize(8);
	mapload();
	setCamera();

	load();
	_dungeonNum = 6;

	if (_randNum == 1)
	{
		_route.push_back(3);
		_route.push_back(8);
	}
	if (_randNum == 3)
	{
		_route.push_back(6);
		_route.push_back(8);
	}
	if (_randNum == 4)
	{
		_route.push_back(2);
		_route.push_back(8);
	}

	_door.resize(2);

	_door[0].x = (8 % 20) * TILESIZE, _door[0].y = (8 / 20) * TILESIZE;
	_door[1].x = (99 % 20) * TILESIZE, _door[1].y = (99 / 20) * TILESIZE;

	_door[0].rc = RectMake(_door[0].x, _door[0].y, TILESIZE * 4, TILESIZE);
	_door[1].rc = RectMake(_door[1].x, _door[1].y, TILESIZE, TILESIZE * 4);


	return S_OK;
}

void dungeon7Scene::update()
{
	nextTest();
}