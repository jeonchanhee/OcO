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
	_mapName = "map/Dungeon2(28x13).map";
 	
	_tileX = TILEVALUE[2][0], _tileY = TILEVALUE[2][1];
	_temp = 29;
	mapload();
	setCamera();
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