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

	_vDoor.resize(2);

	_vDoor[0].x = (8 % 20) * TILESIZE, _vDoor[0].y = (8 / 20) * TILESIZE;
	_vDoor[1].x = (99 % 20) * TILESIZE, _vDoor[1].y = (99 / 20) * TILESIZE;

	_vDoor[0].rc = RectMake(_vDoor[0].x, _vDoor[0].y, TILESIZE * 4, TILESIZE);
	_vDoor[1].rc = RectMake(_vDoor[1].x, _vDoor[1].y, TILESIZE, TILESIZE * 4);

	_vDoor[0].img = IMAGEMANAGER->findImage("updownDoor");
	_vDoor[0].dir = DOOR_UPDOWN;

	_vDoor[1].img = IMAGEMANAGER->findImage("rightDoor");
	_vDoor[1].dir = DOOR_RIGHT;

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
	_enemyBullet->update();
}

void dungeon7Scene::setMonster()
{
	//Ȱ����
	int id[4][2];
	id[0][0] = 630 % _temp, id[0][1] = 630 / _temp;
	id[1][0] = 495 % _temp, id[1][1] = 495 / _temp;
	id[2][0] = 484 % _temp, id[2][1] = 484 / _temp;
	id[3][0] = 209 % _temp, id[3][1] = 209 / _temp;
	for (int i = 0; i < 4; i++)
	{
		setArrow(id[i][0], id[i][1]);
	}

	//ū����
	setBigBat(555 % _temp, 555 / _temp);

	//��ǥ����
	setMusicAngel(530 % _temp, 530 / _temp);

	//��
	setCow(346 % _temp, 346 / _temp);
	
	//����
	id[2][0];
	id[0][0] = 142 % _temp, id[0][1] = 142 / _temp;
	id[1][0] = 159 % _temp, id[1][1] = 159 / _temp;
	for (int i = 0; i < 2; i++)
	{
		setDogBone(id[i][0], id[i][1]);
	}

	//�ۺ���
	setBat(105 % _temp, 105 / _temp);

	//�ۻ���
	setRedBat(115 % _temp, 115 / _temp);

	//ūĮ��
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
