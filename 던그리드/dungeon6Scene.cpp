#include "stdafx.h"
#include "dungeon6Scene.h"


dungeon6Scene::dungeon6Scene()
{
}


dungeon6Scene::~dungeon6Scene()
{
}

HRESULT dungeon6Scene::init()
{
	_isMapSet = true;
	chooseMap(7);
	selectSize(7);
	mapload();
	setCamera();

	load();

	_dungeonNum = 5;

	if (_randNum == 2 || _randNum == 4)
	{
		_route.push_back(5);
	}
	if (_randNum == 3)
	{
		_route.push_back(2);
	}

	_door.resize(1);

	_door[0].x = (2 % 25) * TILESIZE, _door[0].y = (2 / 25) * TILESIZE;
	_door[0].rc = RectMake(_door[0].x, _door[0].y, TILESIZE * 4, TILESIZE);

	_door[0].img = IMAGEMANAGER->findImage("updownDoor");
	_door[0].dir = DOOR_UPDOWN;

	setDoor();
	setMonster();
	return S_OK;
}

void dungeon6Scene::update()
{
	nextTest();
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
	}
	_enemyBullet->update();
}

void dungeon6Scene::setMonster()
{
	//ū����
	setBigRedBat(353 % _temp, 353 / _temp);

	//ū����
	setBigBat(345 % _temp, 345 / _temp);

	//��
	setCow(528 % _temp, 528 / _temp);
	
	//����
	int id[3][2];
	id[0][0] = 679 % _temp, id[0][1] = 679 / _temp;
	id[1][0] = 686 % _temp, id[1][1] = 686 / _temp;
	id[2][0] = 692 % _temp, id[2][1] = 692 / _temp;
	for (int i = 0; i < 3; i++)
	{
		setDogBone(id[i][0], id[i][1]);
	}
	
	//Ȱ����
	id[0][0] = 595 % _temp, id[0][1] = 595 / _temp;
	id[1][0] = 485 % _temp, id[1][1] = 485 / _temp;
	for (int i = 0; i < 2; i++)
	{
		setArrow(id[i][0], id[i][1]);
	}
	
	//�ۺ���
	setBat(408 % _temp, 408 / _temp);

	//ūĮ��
	id[0][0] = 221 % _temp, id[0][1] = 221 / _temp;
	id[1][0] = 212 % _temp, id[1][1] = 212 / _temp;
	for (int i = 0; i < 2; i++)
	{
		setBigBone(id[i][0], id[i][1], i);
	}
}
