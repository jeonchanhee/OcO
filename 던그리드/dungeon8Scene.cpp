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
	setMonster();
	return S_OK;
}

void dungeon8Scene::update()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
	}
}

void dungeon8Scene::setMonster()
{
	//��
	setCow(415 % _temp, 415 / _temp);

	//ū����
	setBigRedBat(114 % _temp, 114 / _temp);

	//��ǥ����
	setMusicAngel(104 % _temp, 104 / _temp);

	//ūĮ��
	int id[3][2];
	id[0][0] = 408 % _temp, id[0][1] = 408 / _temp;
	id[1][0] = 409 % _temp, id[1][1] = 409 / _temp;
	id[2][0] = 410 % _temp, id[2][1] = 410 / _temp;
	for (int i = 0; i < 3; i++)
	{
		setBigBone(id[i][0], id[i][1], i);
	}

	//����
	setDogBone(410 % _temp, 410 / _temp);

	//�۰���
	setRedBat(209 % _temp, 209 / _temp);

	//�ۺ���
	setBat(208 % _temp, 208 / _temp);
}
