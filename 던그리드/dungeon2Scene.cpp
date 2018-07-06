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
	//setCamera();
	_isMapSet = true;
	_mapName = "map/Dungeon3(20x13).map";
 	
	_tileX = TILEVALUE[3][0], _tileY = TILEVALUE[3][1];
	_temp = 100;
	mapload();
	setCamera();
	setMonster();
	return S_OK;
}

void dungeon2Scene::update()
{
}

//void dungeon2Scene::render()
//{
//}
//
//void dungeon2Scene::release()
//{
//}

void dungeon2Scene::setCamera(void)
{
	CAMERAMANAGER->setCameraCenter(PointMake(0, 0));
}

void dungeon2Scene::setMonster()
{
	//°³»À
	int id[2][2];
	id[0][0] = 1107 % _temp, id[0][1] = 1107 / _temp;
	id[1][0] = 1112 % _temp, id[1][1] = 1112 / _temp;
	for (int i = 0; i < 2; i++)
	{
		setDogBone(id[i][0], id[i][1]);
	}
	//È°ÀïÀÌ
	id[0][0] = 505 % _temp, id[0][1] = 505 / _temp;
	id[1][0] = 514 % _temp, id[1][1] = 514 / _temp;
	for (int i = 0; i < 2; i++)
	{
		setArrow(id[i][0], id[i][1]);
	}
	//Å«Ä®»À
	id[0][0] = 810 % _temp, id[0][1] = 810 / _temp;
	id[1][0] = 510 % _temp, id[1][1] = 510 / _temp;
	for (int i = 0; i < 2; i++)
	{
		setBigBone(id[i][0], id[i][1]);
	}
	//ÀÛº¸¹Ú
	setBat(303 % _temp, 303 / _temp);
	//ÀÛ°¥¹Ú
	setRedBat(318 % _temp, 318 / _temp);

}



