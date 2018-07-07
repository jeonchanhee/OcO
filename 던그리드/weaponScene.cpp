#include "stdafx.h"
#include "weaponScene.h"


weaponScene::weaponScene()
{
}


weaponScene::~weaponScene()
{
}

HRESULT weaponScene::init()
{
	_isMapSet = true;
	chooseMap(11);
	selectSize(11);
	mapload();
	setCamera();

	load();

	_dungeonNum = 10;

	if (_randNum == 2)
	{
		_route.push_back(5);
		_route.push_back(8);
	}
	if (_randNum == 3)
	{
		_route.push_back(2);
		_route.push_back(8);
	}
	if (_randNum == 4)
	{
		_route.push_back(10);
		_route.push_back(2);
	}

	_door.resize(2);

	_door[0].x = (150 % 25) * TILESIZE, _door[0].y = (150 / 25) * TILESIZE;
	_door[1].x = (174 % 25) * TILESIZE, _door[1].y = (174 / 25) * TILESIZE;

	_door[0].img = IMAGEMANAGER->findImage("leftDoor");
	_door[0].dir = DOOR_LEFT;
	_door[1].img = IMAGEMANAGER->findImage("rightDoor");
	_door[1].dir = DOOR_RIGHT;

	for (int i = 0; i < 2; i++)
	{
		_door[i].rc = RectMake(_door[i].x, _door[i].y, TILESIZE, TILESIZE * 4);
	}

	setDoor();

	return S_OK;
}

void weaponScene::update()
{
	nextTest();
}