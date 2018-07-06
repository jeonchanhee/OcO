#include "stdafx.h"
#include "dungeon3Scene.h"


dungeon3Scene::dungeon3Scene()
{
}


dungeon3Scene::~dungeon3Scene()
{
}

HRESULT dungeon3Scene::init()
{
	_isMapSet = true;
	chooseMap(4);
	selectSize(4);
	mapload();
	setCamera();

	load();

	_dungeonNum = 2;

	if (_randNum == 1)
	{
		_route.push_back(2);
		_route.push_back(7);
	}
	
	_door.resize(2);

	_door[0].x = (2 % 30) * TILESIZE, _door[0].y = (2 / 30) * TILESIZE;
	_door[1].x = (474 % 30) * TILESIZE, _door[1].y = (474 / 30) * TILESIZE;

	for (int i = 0; i < 2; i++)
	{
		_door[i].rc = RectMake(_door[i].x, _door[i].y, TILESIZE * 4, TILESIZE);
	}
	return S_OK;
}


void dungeon3Scene::update()
{
	nextTest();
}