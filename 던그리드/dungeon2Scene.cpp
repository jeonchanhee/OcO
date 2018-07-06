#include "stdafx.h"
#include "dungeon2Scene.h"


dungeon2Scene::dungeon2Scene()
{
}


dungeon2Scene::~dungeon2Scene()
{
}

HRESULT dungeon2Scene::init()
{
	_isMapSet = true;
	chooseMap(3);
	selectSize(3);
	mapload();
	setCamera();
	setMonster();
	return S_OK;
}

void dungeon2Scene::update()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
	}
}

//몬스터 위치 잡아주는 함수
void dungeon2Scene::setMonster()
{
	//개뼈
	int id[2][2];
	id[0][0] = 1107 % _temp, id[0][1] = 1107 / _temp;
	id[1][0] = 1112 % _temp, id[1][1] = 1112 / _temp;
	for (int i = 0; i < 2; i++)
	{
		setDogBone(id[i][0], id[i][1]);
	}
	//활쟁이
	id[0][0] = 505 % _temp, id[0][1] = 505 / _temp;
	id[1][0] = 514 % _temp, id[1][1] = 514 / _temp;
	for (int i = 0; i < 2; i++)
	{
		setArrow(id[i][0], id[i][1]);
	}
	//큰칼뼈
	id[0][0] = 810 % _temp, id[0][1] = 810 / _temp;
	id[1][0] = 510 % _temp, id[1][1] = 510 / _temp;
	for (int i = 0; i < 2; i++)
	{
		setBigBone(id[i][0], id[i][1], i);
	}
	//작보박
	setBat(303 % _temp, 303 / _temp);
	//작갈박
	setRedBat(318 % _temp, 318 / _temp);

}



