#include "stdafx.h"
#include "dungeon5Scene.h"
#include "Player.h"

dungeon5Scene::dungeon5Scene()
{
}


dungeon5Scene::~dungeon5Scene()
{
}

HRESULT dungeon5Scene::init()
{
	dungeonScene::init();
	IMAGEMANAGER->addImage("����5�ȼ�",4704,2688);
	HPEN pen, oldPen;
	pen = CreatePen(BS_SOLID, 25, RGB(0, 255, 0));
	oldPen = (HPEN)SelectObject(IMAGEMANAGER->findImage("����5�ȼ�")->getMemDC(), pen);
	
	LineMake(IMAGEMANAGER->findImage("����5�ȼ�")->getMemDC(), 3080, 1825, 3728, 1188);
	LineMake(IMAGEMANAGER->findImage("����5�ȼ�")->getMemDC(), 1352, 2040, 1908, 2583);
	LineMake(IMAGEMANAGER->findImage("����5�ȼ�")->getMemDC(), 2768, 958, 2595, 785);
	LineMake(IMAGEMANAGER->findImage("����5�ȼ�")->getMemDC(), 3150, 1065, 3065, 975);

	oldPen = (HPEN)SelectObject(IMAGEMANAGER->findImage("����5�ȼ�")->getMemDC(), pen);
	SelectObject(IMAGEMANAGER->findImage("����5�ȼ�")->getMemDC(), oldPen);

	SelectObject(IMAGEMANAGER->findImage("����5�ȼ�")->getMemDC(), oldPen);
	//����  ===== 
	DeleteObject(oldPen);
	DeleteObject(pen);

//	_isMapSet = true;
	chooseMap(6);
	selectSize(6);
	mapload();
	setCamera();

	load();

	_dungeonNum = 4;

	if (_randNum == 2)
	{
		_route.push_back(10);
		_route.push_back(6);
		_route.push_back(11);
	}
	if (_randNum == 4)
	{
		_route.push_back(1);
		_route.push_back(6);
		_route.push_back(10);
	}

	_vDoor.resize(3);

	_vDoor[0].x = (850 % 50) * TILESIZE, _vDoor[0].y = (850 / 50) * TILESIZE;
	_vDoor[1].x = (1375 % 50) * TILESIZE, _vDoor[1].y = (1375 / 50) * TILESIZE;
	_vDoor[2].x = (448 % 50) * TILESIZE, _vDoor[2].y = (448 / 50) * TILESIZE;

	_vDoor[0].rc = RectMake(_vDoor[0].x, _vDoor[0].y, TILESIZE, TILESIZE * 4);
	_vDoor[2].rc = RectMake(_vDoor[2].x, _vDoor[2].y, TILESIZE, TILESIZE * 4);
	_vDoor[1].rc = RectMake(_vDoor[1].x, _vDoor[1].y, TILESIZE * 4, TILESIZE);

	_vDoor[0].img = IMAGEMANAGER->findImage("leftDoor");
	_vDoor[0].dir = DOOR_LEFT;

	_vDoor[1].img = IMAGEMANAGER->findImage("updownDoor");
	_vDoor[1].dir = DOOR_UPDOWN;

	_vDoor[2].img = IMAGEMANAGER->findImage("rightDoor");
	_vDoor[2].dir = DOOR_RIGHT;

	setDoor();
	setMonster();

	setMinimap();
	
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_minimap->setEnemyXY(((_vEnemy[i]->getX() * 300) / (_tileX*TILESIZE)), ((_vEnemy[i]->getY() * 150) / (_tileY*TILESIZE)));
	}
	setDoorMinimap();

	_mapValue[4] = "T";
	return S_OK;
}

void dungeon5Scene::update()
{
	dungeonScene::update();
	nextTest();
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
		int idx = _viEnemy - _vEnemy.begin();
		_minimap->changeEnemyXY(idx, (((*_viEnemy)->getX() * 300) / (_tileX*TILESIZE)), (((*_viEnemy)->getY() * 150) / (_tileY*TILESIZE)));
	}
	MusicAngelBulletFire();
	_enemyBullet->update();
}

void dungeon5Scene::render()
{
	dungeonScene::render();
	
	_player->render();

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		IMAGEMANAGER->findImage("gray")->alphaRender(DC, CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, 450);
		_tabMap->render(UIDC, 0, 0);
		dungeonScene::minimapIconRender();
	}
}
void dungeon5Scene::setMonster()
{
	//��ǥ����
	setMusicAngel(256 % _temp, 256 / _temp);
	
	//ūĮ��
	int id[3][2];
	id[0][0] = 365 % _temp, id[0][1] = 365 / _temp;
	id[1][0] = 1005 % _temp, id[1][1] = 1005 / _temp;
	id[2][0] = 1325 % _temp, id[2][1] = 1325 / _temp;
	for (int i = 0; i < 3; i++)
	{
		setBigBone(id[i][0], id[i][1],i);
	}

	//�ۻ���
	id[0][0] = 318 % _temp, id[0][1] = 318 / _temp;
	id[1][0] = 811 % _temp, id[1][1] = 811 / _temp;
	for (int i = 0; i < 2; i++)
	{
		setRedBat(id[i][0], id[i][1]);
	}

	//�ۺ���
	setBat(381 % _temp, 318 / _temp);

	//Ȱ����
	id[0][0] = 535 % _temp, id[0][1] = 535 / _temp;
	id[1][0] = 1027 % _temp, id[1][1] = 1027 / _temp;
	for (int i = 0; i < 2; i++)
	{
		setArrow(id[i][0], id[i][1]);
	}

	//ū����
	setBigRedBat(817 % _temp, 817 / _temp);

	//ū����
	setBigBat(293 % _temp, 293 / _temp);

}
