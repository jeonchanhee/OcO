#include "stdafx.h"
#include "foodScene.h"


foodScene::foodScene()
{
}


foodScene::~foodScene()
{
}

HRESULT foodScene::init()
{
	_isMapSet = true;
	chooseMap(2);
	selectSize(2);
	mapload();
	setCamera();
	return S_OK;
}
