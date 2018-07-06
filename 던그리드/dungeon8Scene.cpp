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
	return S_OK;
}