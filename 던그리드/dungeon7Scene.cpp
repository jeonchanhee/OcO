#include "stdafx.h"
#include "dungeon7Scene.h"
#include "Player.h"

dungeon7Scene::dungeon7Scene()
{
}


dungeon7Scene::~dungeon7Scene()
{
}

HRESULT dungeon7Scene::init()
{
	dungeonScene::init();

//	_isMapSet = true;
	chooseMap(8);
	selectSize(8);
	mapload();
	//setCamera();

	load();
	_dungeonNum = 6;

	if (_randNum == 1)
	{
		_route.push_back(3);
		_route.push_back(8);
	}
	if (_randNum == 3)
	{
		_route.push_back(6);
		_route.push_back(11);
	}
	if (_randNum == 4)
	{
		_route.push_back(2);
		_route.push_back(8);
	}

	doorInit();
	setDoor();
	setMonster();

	if (_mapValue[_dungeonNum] == "F")
		setMonster();

	setMinimap();
	setDoorMinimap();

	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_minimap->setEnemyXY(((_vEnemy[i]->getX() * 300) / (_tileX*TILESIZE)), ((_vEnemy[i]->getY() * 150) / (_tileY*TILESIZE)));
	}

	_player->setPlayerX(_vDoor[0].x + TILESIZE * 2);
	_player->setPlayerY(_vDoor[0].y);
	//_mapValue[_dungeonNum] = "T";

	return S_OK;
}

void dungeon7Scene::doorInit()
{
	_vDoor.resize(2);

	_vDoor[0].x = (8 % 20) * TILESIZE, _vDoor[0].y = (8 / 20) * TILESIZE;
	_vDoor[1].x = (99 % 20) * TILESIZE, _vDoor[1].y = (99 / 20) * TILESIZE;

	_vDoor[0].rc = RectMake(_vDoor[0].x, _vDoor[0].y, TILESIZE * 4, TILESIZE);
	_vDoor[1].rc = RectMake(_vDoor[1].x, _vDoor[1].y, TILESIZE, TILESIZE * 4);

	_vDoor[0].img = IMAGEMANAGER->findImage("updownDoor");
	_vDoor[0].dir = DOOR_UPDOWN;

	_vDoor[1].img = IMAGEMANAGER->findImage("rightDoor");
	_vDoor[1].dir = DOOR_RIGHT;

	for (int i = 0; i < 4; i++)
	{
		_tiles[8 + i].object = OBJ_DOOR2;
		_tiles[99 + i * 20].object = OBJ_DOOR2;
	}
}

void dungeon7Scene::update()
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

	redBatBullet();
	_radBatBullet->bulletframe("fatherBatBullet2");
	_radBatBullet->update();
}

void dungeon7Scene::render()
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

void dungeon7Scene::setMonster()
{
	//»∞¿Ô¿Ã
	int id[4][2];
	id[0][0] = 630 % _temp, id[0][1] = 630 / _temp;
	id[1][0] = 495 % _temp, id[1][1] = 495 / _temp;
	id[2][0] = 484 % _temp, id[2][1] = 484 / _temp;
	id[3][0] = 209 % _temp, id[3][1] = 209 / _temp;
	for (int i = 0; i < 4; i++)
	{
		setArrow(id[i][0], id[i][1]);
	}

	//≈´∫∏π⁄
	setBigBat(555 % _temp, 555 / _temp);

	//¿Ω«•ø‰¡§
	setMusicAngel(530 % _temp, 530 / _temp);

	//º“
	setCow(346 % _temp, 346 / _temp);
	
	//∞≥ª¿
	id[2][0];
	id[0][0] = 142 % _temp, id[0][1] = 142 / _temp;
	id[1][0] = 159 % _temp, id[1][1] = 159 / _temp;
	for (int i = 0; i < 2; i++)
	{
		setDogBone(id[i][0], id[i][1]);
	}

	//¿€∫∏π⁄
	setBat(105 % _temp, 105 / _temp);

	//¿€ª°π⁄
	setRedBat(115 % _temp, 115 / _temp);

	//≈´ƒÆª¿
	id[4][0];
	id[0][0] = 743 % _temp, id[0][1] = 743 / _temp;
	id[1][0] = 756 % _temp, id[1][1] = 756 / _temp;
	id[2][0] = 747 % _temp, id[2][1] = 747 / _temp;
	id[3][0] = 750 % _temp, id[3][1] = 750 / _temp;
	for (int i = 0; i < 4; i++)
	{
		setBigBone(id[i][0], id[i][1], i);
	}
}
