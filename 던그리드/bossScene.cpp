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
	setBossMon();
	return S_OK;
}

void bossScene::update()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
	}
}

void bossScene::setBossMon()
{
	setBoss();

}
