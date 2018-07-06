#include "stdafx.h"
#include "dungeon5Scene.h"


dungeon5Scene::dungeon5Scene()
{
}


dungeon5Scene::~dungeon5Scene()
{
}

HRESULT dungeon5Scene::init()
{
	_isMapSet = true;
	chooseMap(6);
	selectSize(6);
	mapload();
	setCamera();
	setMonster();
	return S_OK;
}

void dungeon5Scene::update()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
	}
}

void dungeon5Scene::setMonster()
{
	//��ǥ����
	setMusicAngel(256 % _temp, 256 / _temp);
	
	//ūĮ��
	int id[3][2];
	id[0][0] = 365 % _temp, id[0][1] = 365 / _temp;
	id[1][0] = 1005 % _temp, id[1][1] = 1005 / _temp;
	id[2][0] = 1325 % _temp, id[2][1] = 1325 / _temp;
	for (int i = 0; i < 3; i++)
	{
		setBigBone(id[i][0], id[i][1],i);
	}

	//�ۻ���
	id[0][0] = 318 % _temp, id[0][1] = 318 / _temp;
	id[1][0] = 811 % _temp, id[1][1] = 811 / _temp;
	for (int i = 0; i < 2; i++)
	{
		setRedBat(id[i][0], id[i][1]);
	}

	//�ۺ���
	setBat(381 % _temp, 318 / _temp);

	//Ȱ����
	id[0][0] = 535 % _temp, id[0][1] = 535 / _temp;
	id[1][0] = 1027 % _temp, id[1][1] = 1027 / _temp;
	for (int i = 0; i < 2; i++)
	{
		setArrow(id[i][0], id[i][1]);
	}

	//ū����
	setBigRedBat(817 % _temp, 817 / _temp);

	//ū����
	setBigBat(293 % _temp, 293 / _temp);

}
