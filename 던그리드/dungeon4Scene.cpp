#include "stdafx.h"
#include "dungeon4Scene.h"
#include "Player.h"

dungeon4Scene::dungeon4Scene()
{
}


dungeon4Scene::~dungeon4Scene()
{
}

HRESULT dungeon4Scene::init()
{
	dungeonScene::init();

//	_isMapSet = true;
	chooseMap(5);
	selectSize(5);
	mapload();
	//setCamera();
	
	load();

	_dungeonNum = 3;

	if (_randNum == 1)
	{
		_route.push_back(2);
	}
	if (_randNum == 3 || _randNum == 4)
	{
		_route.push_back(2);
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

void dungeon4Scene::doorInit()
{
	_vDoor.resize(1);

	_vDoor[0].x = (361 % 25) * TILESIZE;
	_vDoor[0].y = (361 / 25) * TILESIZE;
	_vDoor[0].rc = RectMake(_vDoor[0].x, _vDoor[0].y, TILESIZE * 4, TILESIZE);
	_vDoor[0].img = IMAGEMANAGER->findImage("updownDoor");
	_vDoor[0].dir = DOOR_UPDOWN;

	for (int i = 0; i < 4; i++)
	{
		_tiles[361 + i].object = OBJ_DOOR2;
	}
}

void dungeon4Scene::update()
{
	dungeonScene::update();
	nextTest();

	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
		int idx = _viEnemy - _vEnemy.begin();
		_minimap->changeEnemyXY(idx, (((*_viEnemy)->getX() * 300) / (_tileX*TILESIZE)), (((*_viEnemy)->getY() * 150) / (_tileY*TILESIZE)));
	}
	MusicAngelBulletFire();
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
}
void dungeon4Scene::render()
{
	dungeonScene::render();

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

void dungeon4Scene::setMonster()
{
	//Å«º¸¹Ú
	setBigBat(103 % _temp, 103 / _temp);

	//À½Ç¥¿äÁ¤
	setMusicAngel(262 % _temp, 262 / _temp);
	
	//È°ÀïÀÌ
	setArrow(258 % _temp, 258 / _temp);

	//È²¼Ò
	setCow(328 % _temp, 328 / _temp);

	//Å«Ä®»À
	setBigBone(338 % _temp, 338 / _temp, 1);

	//°³»À
	int id[2][2];
	id[0][0] = 167 % _temp, id[0][1] = 167 / _temp;
	id[1][0] = 156 % _temp, id[1][1] = 156 / _temp;

	for (int i = 0; i < 2; i++)
	{
		setDogBone(id[i][0], id[i][1]);
	}
}
