#include "stdafx.h"
#include "weaponScene.h"


weaponScene::weaponScene()
{
}


weaponScene::~weaponScene()
{
}

HRESULT weaponScene::init()
{
	_isMapSet = true;
	chooseMap(11);
	selectSize(11);
	mapload();
	setCamera();
	return S_OK;
}