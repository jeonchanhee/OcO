#include "stdafx.h"
#include "dungeon2Scene.h"
#include "Player.h"

dungeon2Scene::dungeon2Scene()
{
}


dungeon2Scene::~dungeon2Scene()
{
}

HRESULT dungeon2Scene::init()
{
	dungeonScene::init();

	IMAGEMANAGER->addImage("던전2픽셀", 1920, 1152);

	HPEN pen, oldPen;
	pen = CreatePen(BS_SOLID, 25, RGB(0, 255, 0));
	oldPen = (HPEN)SelectObject(IMAGEMANAGER->findImage("던전2픽셀")->getMemDC(), pen);

	LineMake(IMAGEMANAGER->findImage("던전2픽셀")->getMemDC(), 290, 976, 470, 1145);
	LineMake(IMAGEMANAGER->findImage("던전2픽셀")->getMemDC(), 1445, 1150, 1625, 975);
	oldPen = (HPEN)SelectObject(IMAGEMANAGER->findImage("던전2픽셀")->getMemDC(), pen);
	SelectObject(IMAGEMANAGER->findImage("던전2픽셀")->getMemDC(), oldPen);

	SelectObject(IMAGEMANAGER->findImage("던전2픽셀")->getMemDC(), oldPen);
	//제거  ===== 
	DeleteObject(oldPen);
	DeleteObject(pen);

	_isMapSet = true;
	chooseMap(3);
	selectSize(3);
	mapload();
	setCamera();

	load();

	_dungeonNum = 1;

	doorInit();
	setDoor();
	
	setMonster();
	return S_OK;
}

void dungeon2Scene::update()
{
	dungeonScene::update();
	nextTest();
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
	}
	bigbatbulletFire();
	_enemyBullet->bulletframe("fatherBatBullet2");
	_enemyBullet->update();
	

	bigRadbatbulletFire();
	for (int i = 0; i < 20; i++)
	{
		_bigRadBatBullet[i]->bulletframe("fatherBatBullet2");
		_bigRadBatBullet[i]->update();
	}
}

void dungeon2Scene::setRandMapNum()
{
	if (_randNum == 1)
	{
		_route.push_back(1);
		_route.push_back(4);
		_route.push_back(3);
	}
	if (_randNum == 3)
	{
		_route.push_back(1);
		_route.push_back(4);
		_route.push_back(7);
	}
	if (_randNum == 4)
	{
		_route.push_back(11);
		_route.push_back(4);
		_route.push_back(7);
	}
}

void dungeon2Scene::doorInit()
{
	_vDoor.resize(3);

	_vDoor[0].x = (500 % 100) * TILESIZE, _vDoor[0].y = (500 / 100) * TILESIZE;
	_vDoor[1].x = (8 % 100) * TILESIZE, _vDoor[1].y = (8 / 100) * TILESIZE;
	_vDoor[2].x = (1208 % 100) * TILESIZE, _vDoor[2].y = (1208 / 100) * TILESIZE;

	_vDoor[0].rc = RectMake(_vDoor[0].x, _vDoor[0].y, TILESIZE, TILESIZE * 4);
	_vDoor[0].dir = DOOR_LEFT;
	_vDoor[0].img = IMAGEMANAGER->findImage("leftDoor");

	for (int i = 1; i < 3; i++)
	{
		_vDoor[i].rc = RectMake(_vDoor[i].x, _vDoor[i].y, TILESIZE * 4, TILESIZE);
		_vDoor[i].dir = DOOR_UPDOWN;
		_vDoor[i].img = IMAGEMANAGER->findImage("updownDoor");
	}
}
//
//void dungeon2Scene::update()
//{
//	dungeonScene::update();
//	nextTest();
//	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
//	{
//		(*_viEnemy)->update();
//		_vDoor[i].rc = RectMake(_vDoor[i].x, _vDoor[i].y, TILESIZE * 4, TILESIZE);
//		_vDoor[i].dir = DOOR_UPDOWN;
//		_vDoor[i].img = IMAGEMANAGER->findImage("updownDoor");
//	}
//}



//void dungeon2Scene::update()
//{
//	dungeonScene::update();
//	nextTest();
//	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
//	{
//		(*_viEnemy)->update();
//	}
//}

//몬스터 위치 잡아주는 함수
void dungeon2Scene::setMonster()
{
	
	//개뼈
	int id[2][2];
	id[0][0] = 810 % _temp, id[0][1] = 810 / _temp;
	id[1][0] = 510 % _temp, id[1][1] = 510 / _temp;
	for (int i = 0; i < 2; i++)
	{
		setDogBone(id[i][0], id[i][1]);
	}
	//활쟁이
	id[0][0] = 505 % _temp, id[0][1] = 505 / _temp;
	id[1][0] = 514 % _temp, id[1][1] = 514 / _temp;
	for (int i = 0; i < 2; i++)
	{
		setArrow(id[i][0], id[i][1]);
	}
	//큰칼뼈
	id[0][0] = 1107 % _temp, id[0][1] = 1107 / _temp;
	id[1][0] = 1112 % _temp, id[1][1] = 1112 / _temp;
	for (int i = 0; i < 2; i++)
	{
		setBigBone(id[i][0], id[i][1], i);
	}
	//작보박
	setBat(303 % _temp, 303 / _temp);
	//작갈박
	setRedBat(318 % _temp, 318 / _temp);

	setBigBat(410 % _temp, 410 / _temp);
	setBigRedBat(414 % _temp, 414 / _temp);
}



