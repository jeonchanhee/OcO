#include "stdafx.h"
#include "bossScene.h"
#include "Player.h"

bossScene::bossScene()
{
}


bossScene::~bossScene()
{
}

HRESULT bossScene::init()
{
	dungeonScene::init();
//	_isMapSet = true;
	chooseMap(10);
	selectSize(10);
	mapload();
	setCamera();

	_dungeonNum = 8;

	load();

	doorInit();
	setDoor();

	setMinimap();
	setDoorMinimap();

	if (_randNum == 5)
	{
		_route.push_back(1);
		_route.push_back(8);
	}

	setBossMon();

	//_mapValue[_dungeonNum] = "T";
	
	return S_OK;
}

void bossScene::update()
{
	dungeonScene::update();
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
	}
	nextTest();
//	bossSwordFire();
	BossBulletFire();
	_enemyBullet->update();
	EFFECTMANAGER->update();
}

void bossScene::render()
{
	EFFECTMANAGER->render();
	dungeonScene::render();
	EFFECTMANAGER->render();

	_player->render();

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		IMAGEMANAGER->findImage("gray")->alphaRender(DC, CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, 450);
		_tabMap->render(UIDC, 0, 0);
		dungeonScene::minimapIconRender();
		char str[128];
		sprintf_s(str, "%d %d", getCameraPoint().x, getCameraPoint().y);
		TextOut(UIDC, 500, 500, str, strlen(str));
	}
}

void bossScene::doorInit()
{
	_vDoor.resize(2);

	_vDoor[0].x = (650 % 50) * TILESIZE;
	_vDoor[0].y = (650 / 50) * TILESIZE;
	_vDoor[0].rc = RectMake(_vDoor[0].x, _vDoor[0].y, TILESIZE, TILESIZE * 4);
	_vDoor[0].img = IMAGEMANAGER->findImage("leftDoor");
	_vDoor[0].dir = DOOR_LEFT;

	_vDoor[1].x = (670 % 50) * TILESIZE;
	_vDoor[1].y = (670 / 50) * TILESIZE;
	_vDoor[1].rc = RectMake(_vDoor[1].x, _vDoor[1].y, TILESIZE, TILESIZE * 4);
	_vDoor[1].img = IMAGEMANAGER->findImage("rightDoor");
	_vDoor[1].dir = DOOR_RIGHT;
}

void bossScene::setBossMon()
{
	setBoss();
}