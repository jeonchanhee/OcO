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

//	_isMapSet = true;
	chooseMap(1);
	selectSize(1);
	mapload();
	//setCamera();
	

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

	//_mapValue[0] = "T";
	//_player->setGold(10);
	return S_OK;
}

void dungeon1Scene::setRandMapNum()
{
	if (_randNum == 1 || _randNum == 3)
	{
		_route.push_back(2);
		_minimapIcon[0].x = 400, _minimapIcon[0].y = 400;
	}
	if (_randNum == 2)
	{
		_route.push_back(10);
		_minimapIcon[0].x = 400, _minimapIcon[0].y = 400;
	}
	if (_randNum == 4)
	{
		_route.push_back(5);
		_minimapIcon[0].x = 500, _minimapIcon[0].y = 500;
	}
	if (_randNum == 5)
	{
		_route.push_back(9);
		_minimapIcon[0].x = 700, _minimapIcon[0].y = 500;
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

	_player->render();

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		IMAGEMANAGER->findImage("gray")->alphaRender(DC,CAMERAMANAGER->getCameraCenter().x - WINSIZEX/2,CAMERAMANAGER->getCameraCenter().y - WINSIZEY/2,450);
		_tabMap->render(UIDC, 0, 0);
		dungeonScene::minimapIconRender();
		char str[128];
		sprintf_s(str, "%d %d", getCameraPoint().x, getCameraPoint().y);
		TextOut(UIDC, 500, 500, str, strlen(str));
	}
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

