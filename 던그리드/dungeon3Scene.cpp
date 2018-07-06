#include "stdafx.h"
#include "dungeon3Scene.h"


dungeon3Scene::dungeon3Scene()
{
}

dungeon3Scene::~dungeon3Scene()
{
}

HRESULT dungeon3Scene::init()
{
	_isMapSet = true;
	chooseMap(4);
	selectSize(4);
	mapload();
	setCamera();
	setMonster();
	return S_OK;
}

void dungeon3Scene::update()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
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
	setDogBone(390 % _temp, 390 / _temp);

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
