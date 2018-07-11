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

	//_sword = new Bullet;
	//_sword->init(3000);
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
	//_sword->update();
	//bossSwordFire();
	//bossSwordCollision();
	EFFECTMANAGER->update();
}

void bossScene::render()
{

	dungeonScene::render();
	//_sword->swordRender();
	EFFECTMANAGER->render();
}
void bossScene::setBossMon()
{
	setBoss();
}
/*
void bossScene::bossSwordCollision()
{
	for (int i = 0; i < _sword->getVBullet().size(); i++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_sword->getVBullet()[i].rc, &_player->getPlayerRect()))
		{
			_player->hitDamage(3.0f);
			EFFECTMANAGER->play("bossCollisionBullet", (_player->getPlayerRect().right + _player->getPlayerRect().left) / 2, (_player->getPlayerRect().bottom + _player->getPlayerRect().top) / 2);
			//_sword->removeBullet(i);
			break;
		}
	}
}

void bossScene::bossSwordFire()
{
	
	//bossSwordCollision();
	_swordCount++;
	if (_swordCount == 300)
	{
		for (int i = 0; i < 5; i++)
		{
			_sword->bulletFire("bossSword", 600 + i * 200, 100, 0, 0, 1600, false, WIDTH, i);
		}
	}
	else if (_swordCount > 300 && !(_swordCount % 100))
	{
		_sword->changeSpeedAndAngle(_player->getPlayerX(), _player->getPlayerY());
	}
}


*/