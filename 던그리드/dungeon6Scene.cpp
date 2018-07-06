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
	setMonster();
	return S_OK;
}

void dungeon6Scene::update()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
	}
}

void dungeon6Scene::setMonster()
{
	//Å«»¡¹Ú
	setBigRedBat(353 % _temp, 353 / _temp);

	//Å«º¸¹Ú
	setBigBat(345 % _temp, 345 / _temp);

	//¼Ò
	setCow(528 % _temp, 528 / _temp);
	
	//°³»À
	int id[3][2];
	id[0][0] = 679 % _temp, id[0][1] = 679 / _temp;
	id[1][0] = 686 % _temp, id[1][1] = 686 / _temp;
	id[2][0] = 692 % _temp, id[2][1] = 692 / _temp;
	for (int i = 0; i < 3; i++)
	{
		setDogBone(id[i][0], id[i][1]);
	}
	
	//È°ÀïÀÌ
	id[0][0] = 595 % _temp, id[0][1] = 595 / _temp;
	id[1][0] = 485 % _temp, id[1][1] = 485 / _temp;
	for (int i = 0; i < 2; i++)
	{
		setArrow(id[i][0], id[i][1]);
	}
	
	//ÀÛº¸¹Ú
	setBat(408 % _temp, 408 / _temp);

	//Å«Ä®»À
	id[0][0] = 221 % _temp, id[0][1] = 221 / _temp;
	id[1][0] = 212 % _temp, id[1][1] = 212 / _temp;
	for (int i = 0; i < 2; i++)
	{
		setBigBone(id[i][0], id[i][1], i);
	}

}
