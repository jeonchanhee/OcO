#include "stdafx.h"
#include "bossScene.h"
#include "Player.h"

bossScene::bossScene()
{
}


bossScene::~bossScene()
{
}

HRESULT bossScene::init()
{
	dungeonScene::init();
//	_isMapSet = true;
	chooseMap(10);
	selectSize(10);
	mapload();
	setCamera();

	_dungeonNum = 8;

	setBossMon();
	
	return S_OK;
}

void bossScene::update()
{
	dungeonScene::update();
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
	}
//	bossSwordFire();
	BossBulletFire();
	_enemyBullet->update();
	EFFECTMANAGER->update();
}

void bossScene::render()
{

	dungeonScene::render();
	EFFECTMANAGER->render();
}

void bossScene::setBossMon()
{
	setBoss();
}