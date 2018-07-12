#include "stdafx.h"
#include "foodScene.h"
#include "Player.h"

foodScene::foodScene()
{
}


foodScene::~foodScene()
{
}

HRESULT foodScene::init()
{
	dungeonScene::init();

//	_isMapSet = true;
	chooseMap(2);
	selectSize(2);
	mapload();
	setCamera();

	load();

	_dungeonNum = 9;
	setRandMapNum();
	
	doorInit();
	setDoor();
	
	portalInit(299 % 29, 299 / 29);

	_player->setGold(100);

	_foodNpc = new FoodNpc;
	_foodNpc->init(NPC_LEFT_STOP, FOOD_NPC, "¿£ÇÇ½Ã", 1, PointMake((339 % 29)*TILESIZE, (339 / 29) * TILESIZE));

	setMinimap();
	_minimap->setNPCXY(0, (((300 * ((339 % 29)*TILESIZE))/(_tileX*TILESIZE))), ((((339 / 29) * TILESIZE) - 50)*150/(_tileY * TILESIZE)));
	setDoorMinimap();

	_mapValue[9] = "T";
	return S_OK;
}

void foodScene::update()
{
	dungeonScene::update();
	nextTest();
	_foodNpc->update();
}

void foodScene::setRandMapNum()
{
	if (_randNum == 2)
	{
		_route.push_back(1);
		_route.push_back(5);
	}
	if (_randNum == 4)
	{
		_route.push_back(5);
		_route.push_back(11);
		_minimapIcon[9].x = 620, _minimapIcon[9].y = 500;
	}

}
void foodScene::doorInit()
{
	_vDoor.resize(2);

	_vDoor[1].x = (201 % 29) * TILESIZE, _vDoor[1].y = (201 / 29) * TILESIZE;
	_vDoor[0].x = (174 % 29) * TILESIZE, _vDoor[0].y = (174 / 29) * TILESIZE;

	_vDoor[0].img = IMAGEMANAGER->findImage("leftDoor");
	_vDoor[0].dir = DOOR_LEFT;
	_vDoor[1].img = IMAGEMANAGER->findImage("rightDoor");
	_vDoor[1].dir = DOOR_RIGHT;

	for (int i = 0; i < 2; i++)
	{
		_vDoor[i].rc = RectMake(_vDoor[i].x, _vDoor[i].y, TILESIZE, TILESIZE * 4);
	}
}
void foodScene::render()
{
	dungeonScene::render();
	IMAGEMANAGER->render("d_restaurant", DC, (184 % 29)*TILESIZE, (184 / 29)*TILESIZE + 25);
	_foodNpc->render();
	_player->render();

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		IMAGEMANAGER->findImage("gray")->alphaRender(DC, CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, 450);
		_tabMap->render(UIDC, 0, 0);
		dungeonScene::minimapIconRender();
	}
}
