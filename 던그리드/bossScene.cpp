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
	dungeonScene::init();
	_isMapSet = true;
	chooseMap(10);
	selectSize(10);
	mapload();
	setCamera();

	_dungeonNum = 8;

	_sword = new Bullet;
	_sword->init(3000);
	setBossMon();
	EFFECTMANAGER->addEffect("bossSword", "image/enemy/dieEffect(4224x384,11x1).bmp", 4224, 384, 4224 / 11, 384, 5, 0.3f, 1);
	return S_OK;
}

void bossScene::update()
{
	dungeonScene::update();
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
	}
	bossSwordFire();
	BossBulletFire();
	_enemyBullet->update();
	_sword->update();
	bossSwordFire();

	EFFECTMANAGER->update();
}

void bossScene::render()
{
	dungeonScene::render();
	_sword->swordRender();
	EFFECTMANAGER->render();
}
void bossScene::setBossMon()
{
	setBoss();
}

void bossScene::bossSwordFire()
{
	_swordCount++;
	if (_swordCount == 300)
	{
		for (int i = 0; i < 5; i++)
		{
			_sword->bulletFire("bossSword", 600 + i * 200, 100, 0, 0, 1600, false,WIDTH,i);
		}
	}
	else if (_swordCount > 300 && !(_swordCount % 100))
	{
		_sword->changeSpeedAndAngle(PTMOUSE_X, PTMOUSE_Y);
	}
}
