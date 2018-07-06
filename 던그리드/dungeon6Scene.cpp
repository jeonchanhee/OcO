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
	return S_OK;
}