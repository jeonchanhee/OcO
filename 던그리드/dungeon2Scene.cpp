#include "stdafx.h"
#include "dungeon2Scene.h"


dungeon2Scene::dungeon2Scene()
{
}


dungeon2Scene::~dungeon2Scene()
{
}

HRESULT dungeon2Scene::init()
{
	_isMapSet = true;
	chooseMap(3);
	selectSize(3);
	mapload();
	setCamera();

	load();

	_dungeonNum = 1;

	if (_randNum == 1)
	{
		_route.push_back(1);
		_route.push_back(4);
		_route.push_back(3);
	}
	if (_randNum == 3)
	{
		_route.push_back(1);
		_route.push_back(4);
		_route.push_back(7);
	}
	if (_randNum == 4)
	{
		_route.push_back(11);
		_route.push_back(4);
		_route.push_back(7);
	}

	_door.resize(3);

	_door[0].x = (500 % 100) * TILESIZE, _door[0].y = (500 / 100) * TILESIZE;
	_door[1].x = (8 % 100) * TILESIZE, _door[1].y = (8 / 100) * TILESIZE;
	_door[2].x = (1208 % 100) * TILESIZE, _door[2].y = (1208 / 100) * TILESIZE;

	_door[0].rc = RectMake(_door[0].x, _door[0].y, TILESIZE, TILESIZE * 4);

	for (int i = 1; i < 3; i++)
	{
		_door[i].rc = RectMake(_door[i].x, _door[i].y, TILESIZE * 4, TILESIZE);
	}
	return S_OK;
}

void dungeon2Scene::update()
{
	nextTest();
}