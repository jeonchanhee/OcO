#include "stdafx.h"
#include "dungeon4Scene.h"


dungeon4Scene::dungeon4Scene()
{
}


dungeon4Scene::~dungeon4Scene()
{
}

HRESULT dungeon4Scene::init()
{
	_isMapSet = true;
	chooseMap(5);
	selectSize(5);
	mapload();
	setCamera();
	return S_OK;
}

void dungeon4Scene::update()
{
}