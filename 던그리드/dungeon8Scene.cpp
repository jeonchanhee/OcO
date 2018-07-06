#include "stdafx.h"
#include "dungeon8Scene.h"


dungeon8Scene::dungeon8Scene()
{
}


dungeon8Scene::~dungeon8Scene()
{
}

HRESULT dungeon8Scene::init()
{
	_isMapSet = true;
	chooseMap(9);
	selectSize(9);
	mapload();
	setCamera();

	load();
	_dungeonNum = 7;

	if (_randNum == 1 || _randNum == 3 || _randNum == 4)
	{
		_route.push_back(7);
	}

	if (_randNum == 2)
	{
		_route.push_back(11);
	}
	
	_door.resize(1);

	_door[0].x = (250 % 50) * TILESIZE, _door[0].y = (250 / 50) * TILESIZE;
	_door[0].rc = RectMake(_door[0].x, _door[0].y, TILESIZE, TILESIZE * 4);

	return S_OK;
}

void dungeon8Scene::update()
{
	nextTest();
}