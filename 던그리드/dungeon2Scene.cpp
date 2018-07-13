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

	chooseMap(3);
	selectSize(3);
	mapload();
//	setCamera();

	load();

	_dungeonNum = 1;

	setRandMapNum();
	doorInit();
	setDoor();
	
	if(_mapValue[_dungeonNum] == "F")
		setMonster();

	setMinimap();

	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_minimap->setEnemyXY(((_vEnemy[i]->getX() * 300) / (_tileX*TILESIZE)), ((_vEnemy[i]->getY() * 150) / (_tileY*TILESIZE)));
	}
	setDoorMinimap();

	_player->setPlayerX(_vDoor[0].x + TILESIZE * 2);
	_player->setPlayerY(_vDoor[0].y);

	return S_OK;
}

void dungeon2Scene::update()
{
	dungeonScene::update();
	nextTest();
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
		int idx = _viEnemy - _vEnemy.begin();
		_minimap->changeEnemyXY(idx, (((*_viEnemy)->getX() * 300) / (_tileX*TILESIZE)), (((*_viEnemy)->getY() * 150) / (_tileY*TILESIZE)));
	}
	if (_bigbat!=NULL&&!_bigbat->getdiedie())
	{
		bigbatbulletFire();
	}
	_bigBatBullet->bulletframe("fatherBatBullet2");
	if (_start2 != 0)
	{
		_bigBatBullet->update();
	}
	if (_bigbat != NULL && !_bigRedBat->getdiedie())
	{
		bigRadbatbulletFire();
	}
	else
	{
		_start = 1;
	}

		for (int i = 0; i < 20; i++)
		{
			_bigRadBatBullet[i]->bulletframe("fatherBatBullet2");
			if (_start == 1) 
				_bigRadBatBullet[i]->update();
		}
	
	redBatBullet();
	_radBatBullet->bulletframe("fatherBatBullet2");
	_radBatBullet->update();
}

void dungeon2Scene::render()
{
	dungeonScene::render();

	//_player->render();

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

	for (int i = 0; i < 4; i++)
	{
		_tiles[8 + i].object = OBJ_DOOR2;
		_tiles[1208 + i].object = OBJ_DOOR2;
		_tiles[500 + i * 100].object = OBJ_DOOR2;
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
	//
	////개뼈
	int id[2][2];
	//id[0][0] = 810 % _temp, id[0][1] = 810 / _temp;
	//id[1][0] = 510 % _temp, id[1][1] = 510 / _temp;
	//for (int i = 0; i < 2; i++)
	//{
	//	setDogBone(id[i][0], id[i][1]);
	//}
	////활쟁이
	//id[0][0] = 505 % _temp, id[0][1] = 505 / _temp;
	//id[1][0] = 514 % _temp, id[1][1] = 514 / _temp;
	//for (int i = 0; i < 2; i++)
	//{
	//	setArrow(id[i][0], id[i][1]);
	//}
	////큰칼뼈
	id[0][0] = 1107 % _temp, id[0][1] = 1107 / _temp;
	id[1][0] = 1112 % _temp, id[1][1] = 1112 / _temp;
	for (int i = 0; i < 2; i++)
	{
		setBigBone(id[i][0], id[i][1], i);
	}
	//작보박
	setBat(405 % _temp, 405 / _temp);
	//작갈박
	setRedBat(318 % _temp, 318 / _temp);

	setBigBat(410 % _temp, 410 / _temp);
	setBigRedBat(414 % _temp, 414 / _temp);
}



