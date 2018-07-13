#include "stdafx.h"
#include "dungeon3Scene.h"
#include "Player.h"

dungeon3Scene::dungeon3Scene()
{
}

dungeon3Scene::~dungeon3Scene()
{
}

HRESULT dungeon3Scene::init()
{
	dungeonScene::init();


//	_isMapSet = true;
	chooseMap(4);
	selectSize(4);
	mapload();
//	setCamera();

	load();

	_dungeonNum = 2;

	if (_randNum == 1)
	{
		_route.push_back(2);
		_route.push_back(7);
	}
	
	
	doorInit();
	setDoor();
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
//	_mapValue[_dungeonNum] = "T";
	return S_OK;
}

void dungeon3Scene::doorInit()
{
	_vDoor.resize(2);

	_vDoor[0].x = (2 % 30) * TILESIZE, _vDoor[0].y = (2 / 30) * TILESIZE;
	_vDoor[1].x = (474 % 30) * TILESIZE, _vDoor[1].y = (474 / 30) * TILESIZE;

	for (int i = 0; i < 2; i++)
	{
		_vDoor[i].rc = RectMake(_vDoor[i].x, _vDoor[i].y, TILESIZE * 4, TILESIZE);
		_vDoor[i].img = IMAGEMANAGER->findImage("updownDoor");
		_vDoor[i].dir = DOOR_UPDOWN;
	}

	for (int i = 0; i < 4; i++)
	{
		_tiles[2 + i].object = OBJ_DOOR2;
		_tiles[474 + i].object = OBJ_DOOR2;
	}
}

void dungeon3Scene::update()
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
	
	redBatBullet();
	_radBatBullet->bulletframe("fatherBatBullet2");
	_radBatBullet->update();
}

void dungeon3Scene::render()
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

void dungeon3Scene::setMonster()
{
	//큰보박
	setBigBat(102 % _temp, 102 / _temp);

	//작보박
	setBat(99 % _temp, 99 / _temp);

	//작갈박
	setRedBat(142 % _temp, 142 / _temp);

	//개뼈
	setDogBone(396 % _temp, 396 / _temp);

	//활쟁이
	int id2[3][2];
	id2[0][0] = 166 % _temp, id2[0][1] = 166 / _temp;
	id2[1][0] = 275 % _temp, id2[1][1] = 275 / _temp;
	id2[2][0] = 177 % _temp, id2[2][1] = 177 / _temp;
	for (int i = 0; i < 3; i++)
	{
		setArrow(id2[i][0], id2[i][1]);
	}
}
