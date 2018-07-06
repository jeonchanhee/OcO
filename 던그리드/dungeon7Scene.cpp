#include "stdafx.h"
#include "dungeon7Scene.h"


dungeon7Scene::dungeon7Scene()
{
}


dungeon7Scene::~dungeon7Scene()
{
}

HRESULT dungeon7Scene::init()
{
	_isMapSet = true;
	chooseMap(8);
	selectSize(8);
	mapload();
	setCamera();
	return S_OK;
}