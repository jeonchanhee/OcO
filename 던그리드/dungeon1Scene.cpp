#include "stdafx.h"
#include "dungeon1Scene.h"
#include "Player.h"

dungeon1Scene::dungeon1Scene()
{
}


dungeon1Scene::~dungeon1Scene()
{
}

HRESULT dungeon1Scene::init()
{
	dungeonScene::init();

	_isMapSet = true;
	chooseMap(1);
	selectSize(1);
	mapload();
	setCamera();
	

	load();

	_dungeonNum = 0;
	setRandMapNum();

	doorInit();
	setDoor();
	torchInit(192 % 29, 192 / 29);
	portalInit(250 % 29, 250 / 29);
	setDungeonDoor();

	setMinimap();
	setDoorMinimap();
	//_player->setGold(10);
	return S_OK;
}

void dungeon1Scene::setRandMapNum()
{
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

}

void dungeon1Scene::update()
{
	dungeonScene::update();
	nextTest();
	_dungeonDoor.count++;
	if (_dungeonDoor.count == 120)
		_dungeonDoor.ani->start();
}

void dungeon1Scene::render()
{
	dungeonScene::render();
	_dungeonDoor.img->aniRender(DC, _dungeonDoor.x, _dungeonDoor.y, _dungeonDoor.ani);
}

void dungeon1Scene::doorInit()
{
	_vDoor.resize(1);

	_vDoor[0].x = (200 % 29) * TILESIZE;
	_vDoor[0].y = (200 / 29) * TILESIZE;
	_vDoor[0].rc = RectMake(_vDoor[0].x, _vDoor[0].y, TILESIZE, TILESIZE * 4);
	_vDoor[0].img = IMAGEMANAGER->findImage("rightDoor");
	_vDoor[0].dir = DOOR_RIGHT;
}


void dungeon1Scene::setDungeonDoor()
{
	_dungeonDoor.x = (179 % 29) * TILESIZE;
	_dungeonDoor.y = (179 / 29) * TILESIZE - 20;
	_dungeonDoor.img = IMAGEMANAGER->findImage("dungeonDoor");
	_dungeonDoor.count = 0;
	int close[] = { 0,1,2,3,4 };
	KEYANIMANAGER->addDefaultFrameAnimation("closingDungeon", "dungeonDoor", 10, false, false);
	_dungeonDoor.ani = KEYANIMANAGER->findAnimation("closingDungeon");
}

