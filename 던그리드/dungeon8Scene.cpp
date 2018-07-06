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
