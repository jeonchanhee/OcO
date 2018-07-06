#include "stdafx.h"
#include "foodScene.h"


foodScene::foodScene()
{
}


foodScene::~foodScene()
{
}

HRESULT foodScene::init()
{
	_isMapSet = true;
	chooseMap(2);
	selectSize(2);
	mapload();
	setCamera();

	load();

	_dungeonNum = 9;

	if (_randNum == 2)
	{
		_route.push_back(1);
		_route.push_back(5);
	}
	if (_randNum == 4)
	{
		_route.push_back(5);
		_route.push_back(11);
	}

	_door.resize(2);

	_door[1].x = (201 % 29) * TILESIZE, _door[1].y = (201 / 29) * TILESIZE;
	_door[0].x = (174 % 29) * TILESIZE, _door[0].y = (174 / 29) * TILESIZE;

	for (int i = 0; i < 2; i++)
	{
		_door[i].rc = RectMake(_door[i].x, _door[i].y, TILESIZE, TILESIZE * 4);
	}

	return S_OK;
}

void foodScene::update()
{
	nextTest();
}
