#include "stdafx.h"
#include "dungeon4Scene.h"


dungeon4Scene::dungeon4Scene()
{
}


dungeon4Scene::~dungeon4Scene()
{
}

HRESULT dungeon4Scene::init()
{
	_isMapSet = true;
	chooseMap(5);
	selectSize(5);
	mapload();
	setCamera();
	setMonster();
	return S_OK;
}

void dungeon4Scene::update()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
	}
	MusicAngelBulletFire();
	_enemyBullet->update();
}

void dungeon4Scene::setMonster()
{
	//Å«º¸¹Ú
	setBigBat(103 % _temp, 103 / _temp);

	//À½Ç¥¿äÁ¤
	setMusicAngel(262 % _temp, 262 / _temp);
	
	//È°ÀïÀÌ
	setArrow(258 % _temp, 258 / _temp);

	//È²¼Ò
	setCow(328 % _temp, 328 / _temp);

	//Å«Ä®»À
	setBigBone(338 % _temp, 338 / _temp, 1);

	//°³»À
	int id[2][2];
	id[0][0] = 167 % _temp, id[0][1] = 167 / _temp;
	id[1][0] = 156 % _temp, id[1][1] = 156 / _temp;

	for (int i = 0; i < 2; i++)
	{
		setDogBone(id[i][0], id[i][1]);
	}
}
