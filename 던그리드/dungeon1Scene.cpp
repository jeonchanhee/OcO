#include "stdafx.h"
#include "dungeon1Scene.h"


dungeon1Scene::dungeon1Scene()
{
}


dungeon1Scene::~dungeon1Scene()
{
}

HRESULT dungeon1Scene::init()
{
	_isMapSet = true;
	chooseMap(1);
	selectSize(1);
	mapload();
	setCamera();

	load();

	_dungeonNum = 0;

	if (_randNum == 1 || _randNum == 3)
	{
		_route.push_back(2);
	}
	if (_randNum == 2)
	{
		_route.push_back(10);
	}
	if (_randNum == 4)
	{
		_route.push_back(5);
	}

	_door.resize(1);

	_door[0].x = (200 % 29) * TILESIZE;
	_door[0].y = (200 / 29) * TILESIZE;
	_door[0].rc = RectMake(_door[0].x, _door[0].y, TILESIZE, TILESIZE * 4);
	return S_OK;
}

void dungeon1Scene::update()
{
	nextTest();
}