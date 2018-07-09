#include "stdafx.h"
#include "dungeon7Scene.h"


dungeon7Scene::dungeon7Scene()
{
}


dungeon7Scene::~dungeon7Scene()
{
}

HRESULT dungeon7Scene::init()
{
	_isMapSet = true;
	chooseMap(8);
	selectSize(8);
	mapload();
	setCamera();

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
		_route.push_back(8);
	}
	if (_randNum == 4)
	{
		_route.push_back(2);
		_route.push_back(8);
	}

	_door.resize(2);

	_door[0].x = (8 % 20) * TILESIZE, _door[0].y = (8 / 20) * TILESIZE;
	_door[1].x = (99 % 20) * TILESIZE, _door[1].y = (99 / 20) * TILESIZE;

	_door[0].rc = RectMake(_door[0].x, _door[0].y, TILESIZE * 4, TILESIZE);
	_door[1].rc = RectMake(_door[1].x, _door[1].y, TILESIZE, TILESIZE * 4);

	_door[0].img = IMAGEMANAGER->findImage("updownDoor");
	_door[0].dir = DOOR_UPDOWN;

	_door[1].img = IMAGEMANAGER->findImage("rightDoor");
	_door[1].dir = DOOR_RIGHT;

	setDoor();
	setMonster();
	return S_OK;
}

void dungeon7Scene::update()
{
	dungeonScene::update();
	nextTest();
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
	}
	MusicAngelBulletFire();
	_enemyBullet->update();
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
