#include "stdafx.h"
#include "dungeon6Scene.h"


dungeon6Scene::dungeon6Scene()
{
}


dungeon6Scene::~dungeon6Scene()
{
}

HRESULT dungeon6Scene::init()
{
	_isMapSet = true;
	chooseMap(7);
	selectSize(7);
	mapload();
	setCamera();

	load();

	_dungeonNum = 5;

	if (_randNum == 2 || _randNum == 4)
	{
		_route.push_back(5);
	}
	if (_randNum == 3)
	{
		_route.push_back(2);
	}

	_door.resize(1);

	_door[0].x = (2 % 25) * TILESIZE, _door[0].y = (2 / 25) * TILESIZE;
	_door[0].rc = RectMake(_door[0].x, _door[0].y, TILESIZE * 4, TILESIZE);

	return S_OK;
}

void dungeon6Scene::update()
{
	nextTest();
}