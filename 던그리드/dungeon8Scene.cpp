#include "stdafx.h"
#include "dungeon8Scene.h"


dungeon8Scene::dungeon8Scene()
{
}


dungeon8Scene::~dungeon8Scene()
{
}

HRESULT dungeon8Scene::init()
{
	_isMapSet = true;
	chooseMap(9);
	selectSize(9);
	mapload();
	setCamera();

	load();
	_dungeonNum = 7;

	if (_randNum == 1 || _randNum == 3 || _randNum == 4)
	{
		_route.push_back(7);
	}

	if (_randNum == 2)
	{
		_route.push_back(11);
	}
	
	_door.resize(1);

	_door[0].x = (250 % 50) * TILESIZE, _door[0].y = (250 / 50) * TILESIZE;
	_door[0].rc = RectMake(_door[0].x, _door[0].y, TILESIZE, TILESIZE * 4);

	setMonster();
	return S_OK;
}

void dungeon8Scene::update()
{
	nextTest();
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
	}
	_enemyBullet->update();
}

void dungeon8Scene::setMonster()
{
	//소
	setCow(415 % _temp, 415 / _temp);

	//큰갈박
	setBigRedBat(114 % _temp, 114 / _temp);

	//음표요정
	setMusicAngel(104 % _temp, 104 / _temp);

	//큰칼뼈
	int id[3][2];
	id[0][0] = 408 % _temp, id[0][1] = 408 / _temp;
	id[1][0] = 409 % _temp, id[1][1] = 409 / _temp;
	id[2][0] = 410 % _temp, id[2][1] = 410 / _temp;
	for (int i = 0; i < 3; i++)
	{
		setBigBone(id[i][0], id[i][1], i);
	}

	//개뼈
	setDogBone(410 % _temp, 410 / _temp);

	//작갈박
	setRedBat(209 % _temp, 209 / _temp);

	//작보박
	setBat(208 % _temp, 208 / _temp);
}
