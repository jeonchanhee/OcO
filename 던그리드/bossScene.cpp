#include "stdafx.h"
#include "bossScene.h"


bossScene::bossScene()
{
}


bossScene::~bossScene()
{
}

HRESULT bossScene::init()
{
	_isMapSet = true;
	chooseMap(10);
	selectSize(10);
	mapload();
	setCamera();

	_dungeonNum = 8;

	return S_OK;
}