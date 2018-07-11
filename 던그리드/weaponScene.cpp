#include "stdafx.h"
#include "weaponScene.h"
#include "Player.h"

weaponScene::weaponScene()
{
}


weaponScene::~weaponScene()
{
}

HRESULT weaponScene::init()
{
	dungeonScene::init();

	IMAGEMANAGER->addImage("´øÀü10ÇÈ¼¿",2400,1440);
	HPEN pen, oldPen;
	pen = CreatePen(BS_SOLID, 30, RGB(0, 255, 0));
	oldPen = (HPEN)SelectObject(IMAGEMANAGER->findImage("´øÀü10ÇÈ¼¿")->getMemDC(), pen);

	LineMake(IMAGEMANAGER->findImage("´øÀü10ÇÈ¼¿")->getMemDC(), 300, 980, 570, 1246);
	LineMake(IMAGEMANAGER->findImage("´øÀü10ÇÈ¼¿")->getMemDC(), 1740, 1246, 2010, 973);
	SelectObject(IMAGEMANAGER->findImage("´øÀü10ÇÈ¼¿")->getMemDC(), oldPen);
	//Á¦°Å  ===== 
	DeleteObject(oldPen);
	DeleteObject(pen);

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

	_weaponNpc = new WeaponNpc;
	_weaponNpc->init(NPC_LEFT_STOP, WEAPON_NPC, "¿£ÇÇ½Ã", 2, PointMake((290 % 25)*TILESIZE, (290 / 25) * TILESIZE));

	setMinimap();
	_minimap->setNPCXY(0, (((300 * ((290 % 25)*TILESIZE)) / (_tileX*TILESIZE))), ((((290 / 25) * TILESIZE)) * 150 / (_tileY * TILESIZE)));
	setDoorMinimap();
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
	_weaponNpc->update();
}

void weaponScene::render()
{
	dungeonScene::render();
	IMAGEMANAGER->render("d_restaurant", DC, (181 % 25)*TILESIZE, (181 / 25)*TILESIZE + 25);
	_weaponNpc->render();
}
