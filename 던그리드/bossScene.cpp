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

	load();

	doorInit();
	setDoor();

	setMinimap();
	setDoorMinimap();

	if (_randNum == 5)
	{
		_route.push_back(1);
		_route.push_back(8);
	}

	//_sword = new Bullet;
	//_sword->init(3000);
	setBossMon();

	_mapValue[_dungeonNum] = "T";
	
	return S_OK;
}

void bossScene::update()
{
	dungeonScene::update();
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
	}
	nextTest();
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
	EFFECTMANAGER->render();
	dungeonScene::render();
	//_sword->swordRender();
	EFFECTMANAGER->render();

	_player->render();

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		IMAGEMANAGER->findImage("gray")->alphaRender(DC, CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, 450);
		_tabMap->render(UIDC, 0, 0);
		dungeonScene::minimapIconRender();
		char str[128];
		sprintf_s(str, "%d %d", getCameraPoint().x, getCameraPoint().y);
		TextOut(UIDC, 500, 500, str, strlen(str));
	}
}

void bossScene::doorInit()
{
	_vDoor.resize(2);

	_vDoor[0].x = (650 % 50) * TILESIZE;
	_vDoor[0].y = (650 / 50) * TILESIZE;
	_vDoor[0].rc = RectMake(_vDoor[0].x, _vDoor[0].y, TILESIZE, TILESIZE * 4);
	_vDoor[0].img = IMAGEMANAGER->findImage("leftDoor");
	_vDoor[0].dir = DOOR_LEFT;

	_vDoor[1].x = (670 % 50) * TILESIZE;
	_vDoor[1].y = (670 / 50) * TILESIZE;
	_vDoor[1].rc = RectMake(_vDoor[1].x, _vDoor[1].y, TILESIZE, TILESIZE * 4);
	_vDoor[1].img = IMAGEMANAGER->findImage("rightDoor");
	_vDoor[1].dir = DOOR_RIGHT;
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