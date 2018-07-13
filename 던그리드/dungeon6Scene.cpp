#include "stdafx.h"
#include "dungeon6Scene.h"
#include "Player.h"

dungeon6Scene::dungeon6Scene()
{
}


dungeon6Scene::~dungeon6Scene()
{
}

HRESULT dungeon6Scene::init()
{
	dungeonScene::init();

//	_isMapSet = true;
	chooseMap(7);
	selectSize(7);
	mapload();
//	setCamera();

	load();

	_dungeonNum = 5;
	setRandMapNum();
	
	doorInit();
	setDoor();
	portalInit(655 % 25, 655 / 25);

	if (_mapValue[_dungeonNum] == "F")
		setMonster();

	setMinimap();

	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_minimap->setEnemyXY(((_vEnemy[i]->getX() * 300) / (_tileX*TILESIZE)), ((_vEnemy[i]->getY() * 150) / (_tileY*TILESIZE)));
	}

	setDoorMinimap();

	_player->setPlayerX(_vDoor[0].x + TILESIZE * 2);
	_player->setPlayerY(_vDoor[0].y);

	//_mapValue[_dungeonNum] = "T";

	return S_OK;
}

void dungeon6Scene::update()
{
	dungeonScene::update();
	nextTest();
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
		int idx = _viEnemy - _vEnemy.begin();
		_minimap->changeEnemyXY(idx, (((*_viEnemy)->getX() * 300) / (_tileX*TILESIZE)), (((*_viEnemy)->getY() * 150) / (_tileY*TILESIZE)));
	}
	_enemyBullet->update();

	if (!_bigbat->getdiedie())
	{
		bigbatbulletFire();
	}
	_bigBatBullet->bulletframe("fatherBatBullet2");
	if (_start2 != 0)
	{
		_bigBatBullet->update();
	}
	if (!_bigRedBat->getdiedie())
	{
		bigRadbatbulletFire();
	}
	else
	{
		_start = 1;
	}

	for (int i = 0; i < 20; i++)
	{
		_bigRadBatBullet[i]->bulletframe("fatherBatBullet2");
		if (_start == 1)
			_bigRadBatBullet[i]->update();
	}
}

void dungeon6Scene::render()
{
	dungeonScene::render();

	//_player->render();

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

void dungeon6Scene::setRandMapNum()
{
	if (_randNum == 3)
	{
		_route.push_back(2);
	}
	if (_randNum == 2 || _randNum == 4)
	//else
	{
		_route.push_back(5);
	}
}

void dungeon6Scene::doorInit()
{
	_vDoor.resize(1);

	_vDoor[0].x = (2 % 25) * TILESIZE, _vDoor[0].y = (2 / 25) * TILESIZE;
	_vDoor[0].rc = RectMake(_vDoor[0].x, _vDoor[0].y, TILESIZE * 4, TILESIZE);

	_vDoor[0].img = IMAGEMANAGER->findImage("updownDoor");
	_vDoor[0].dir = DOOR_UPDOWN;

	for (int i = 0; i < 4; i++)
	{
		_tiles[2 + i * 25].object = OBJ_DOOR2;
	}
}

void dungeon6Scene::setMonster()
{
	//Å«»¡¹Ú
	setBigRedBat(353 % _temp, 353 / _temp);

	//Å«º¸¹Ú
	setBigBat(345 % _temp, 345 / _temp);

	//¼Ò
	setCow(528 % _temp, 528 / _temp);
	
	//°³»À
	int id[3][2];
	id[0][0] = 679 % _temp, id[0][1] = 679 / _temp;
	id[1][0] = 686 % _temp, id[1][1] = 686 / _temp;
	id[2][0] = 692 % _temp, id[2][1] = 692 / _temp;
	for (int i = 0; i < 3; i++)
	{
		setDogBone(id[i][0], id[i][1]);
	}
	
	//È°ÀïÀÌ
	id[0][0] = 595 % _temp, id[0][1] = 595 / _temp;
	id[1][0] = 485 % _temp, id[1][1] = 485 / _temp;
	for (int i = 0; i < 2; i++)
	{
		setArrow(id[i][0], id[i][1]);
	}
	
	//ÀÛº¸¹Ú
	setBat(408 % _temp, 408 / _temp);

	//Å«Ä®»À
	id[0][0] = 221 % _temp, id[0][1] = 221 / _temp;
	id[1][0] = 212 % _temp, id[1][1] = 212 / _temp;
	for (int i = 0; i < 2; i++)
	{
		setBigBone(id[i][0], id[i][1], i);
	}
}
