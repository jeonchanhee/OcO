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
	setRandMapNum();

	doorInit();
	setDoor();

	return S_OK;
}

void weaponScene::setRandMapNum()
{

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
}
void weaponScene::doorInit()
{
	_vDoor.resize(2);

	_vDoor[0].x = (150 % 25) * TILESIZE, _vDoor[0].y = (150 / 25) * TILESIZE;
	_vDoor[1].x = (174 % 25) * TILESIZE, _vDoor[1].y = (174 / 25) * TILESIZE;

	_vDoor[0].img = IMAGEMANAGER->findImage("leftDoor");
	_vDoor[0].dir = DOOR_LEFT;
	_vDoor[1].img = IMAGEMANAGER->findImage("rightDoor");
	_vDoor[1].dir = DOOR_RIGHT;

	for (int i = 0; i < 2; i++)
	{
		_vDoor[i].rc = RectMake(_vDoor[i].x, _vDoor[i].y, TILESIZE, TILESIZE * 4);
	}

}

void weaponScene::update()
{
	dungeonScene::update();
	nextTest();
}

void weaponScene::render()
{
	dungeonScene::render();
	IMAGEMANAGER->render("d_restaurant", DC, (181 % 25)*TILESIZE, (181 / 25)*TILESIZE + 25);
}
