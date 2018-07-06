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
	return S_OK;
}