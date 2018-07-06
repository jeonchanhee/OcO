#include "stdafx.h"
#include "dungeon4Scene.h"


dungeon4Scene::dungeon4Scene()
{
}


dungeon4Scene::~dungeon4Scene()
{
}

HRESULT dungeon4Scene::init()
{
	_isMapSet = true;
	chooseMap(5);
	selectSize(5);
	mapload();
	setCamera();
	
	load();

	_dungeonNum = 3;

	if (_randNum == 1)
	{
		_route.push_back(2);
	}
	if (_randNum == 3 || _randNum == 4)
	{
		_route.push_back(2);
	}

	_door.resize(1);

	_door[0].x = (361 % 25) * TILESIZE;
	_door[0].y = (361 / 25) * TILESIZE;
	_door[0].rc = RectMake(_door[0].x, _door[0].y, TILESIZE*4, TILESIZE);
	return S_OK;
}

void dungeon4Scene::update()
{
	nextTest();
}