#include "stdafx.h"
#include "dungeon3Scene.h"


dungeon3Scene::dungeon3Scene()
{
}


dungeon3Scene::~dungeon3Scene()
{
}

HRESULT dungeon3Scene::init()
{
	_isMapSet = true;
	chooseMap(4);
	selectSize(4);
	mapload();
	setCamera();
	return S_OK;
}

void dungeon3Scene::update()
{
}