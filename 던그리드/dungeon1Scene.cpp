#include "stdafx.h"
#include "dungeon1Scene.h"


dungeon1Scene::dungeon1Scene()
{
}


dungeon1Scene::~dungeon1Scene()
{
}

HRESULT dungeon1Scene::init()
{
	_isMapSet = true;
	chooseMap(1);
	selectSize(1);
	mapload();
	setCamera();
	return S_OK;
	return S_OK;
}

void dungeon1Scene::update()
{
}
