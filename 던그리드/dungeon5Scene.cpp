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
	return S_OK;
}