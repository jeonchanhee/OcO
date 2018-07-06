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
	return S_OK;
}

void dungeon2Scene::update()
{
}


