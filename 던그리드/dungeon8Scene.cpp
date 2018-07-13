#include "stdafx.h"
#include "dungeon8Scene.h"
#include "Player.h"
#include "RandomDungeon1.h"

dungeon8Scene::dungeon8Scene()
{
}


dungeon8Scene::~dungeon8Scene()
{
}

HRESULT dungeon8Scene::init()
{
	dungeonScene::init();

	//_isMapSet = true;
	chooseMap(9);
	selectSize(9);
	mapload();
	//setCamera();

	load();
	_dungeonNum = 7;

	setRandMapNum();

	doorInit();
	setDoor();
	//setMonster();

	setDungeonDoor();
	portalInit(363 % 50, 363 / 50);

	setMinimap();
	setDoorMinimap();

	//_mapValue[_dungeonNum] = "T";

	_doorRc = RectMake(_dungeonDoor.x + 100, _dungeonDoor.y + 200, 100, 200);

	//_player->setPlayerX(_vDoor[0].x + TILESIZE * 2);
	//_player->setPlayerY(_vDoor[0].y);
	_player->setPlayerX(300);
	_player->setPlayerY(500);
	_time = TIMEMANAGER->getWorldTime();
	return S_OK;
}

void dungeon8Scene::setRandMapNum()
{
	if (_randNum == 1 || _randNum == 3 || _randNum == 4)
	{
		_route.push_back(7);
	}

	if (_randNum == 2)
	{
		_route.push_back(11);
	}
	if (_randNum == 5)
	{
		_route.push_back(9);
	}
}

void dungeon8Scene::doorInit()
{
	_vDoor.resize(1);

	_vDoor[0].x = (250 % 50) * TILESIZE, _vDoor[0].y = (250 / 50) * TILESIZE;
	_vDoor[0].rc = RectMake(_vDoor[0].x, _vDoor[0].y, TILESIZE, TILESIZE * 4);

	_vDoor[0].img = IMAGEMANAGER->findImage("leftDoor");
	_vDoor[0].dir = DOOR_LEFT;
	
	for (int i = 0; i < 4; i++)
	{
		_tiles[250 + i * 50].object = OBJ_DOOR2;
	}
}

void dungeon8Scene::update()
{
	dungeonScene::update();

	if (_time >= TIMEMANAGER->getWorldTime() - 1)
	{
		_player->setPlayerX(_vDoor[0].x + TILESIZE * 3);
		_player->setPlayerY(_vDoor[0].y);
	}

	nextTest();
	//for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	//{
	//	(*_viEnemy)->update();
	//}
	//MusicAngelBulletFire();
	//_enemyBullet->update();

	RECT temp;
	if (IntersectRect(&temp, &_player->getRc(), &_doorRc))
	{
		float size = (temp.right - temp.left)*(temp.bottom - temp.top);
		if (size > 70 && !_enter)
		{
			vector<string> vStr = TXTDATA->txtLoad("random.txt");
			vStr[_randNum - 1] = "T";
			TXTDATA->txtSave("random.txt", vStr);
			_randMap1 = new RandomDungeon1;
			_randMap1->init();
			_enter = true;
			_dungeonDoor.ani->start();
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (!_dungeonDoor.ani->isPlay())
		{
			_dungeonDoor.ani->start();
		}
	}

}

void dungeon8Scene::render()
{
	dungeonScene::render();
	_dungeonDoor.img->aniRender(DC, _dungeonDoor.x, _dungeonDoor.y, _dungeonDoor.ani);
	_player->render();

	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(DC, _doorRc.left, _doorRc.top, _doorRc.right, _doorRc.bottom);
		Rectangle(DC, _player->getRc().left, _player->getRc().top, _player->getRc().right, _player->getRc().bottom);
	}
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		IMAGEMANAGER->findImage("gray")->alphaRender(DC, CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, 450);
		_tabMap->render(UIDC, 0, 0);
		dungeonScene::minimapIconRender();
	}
}

void dungeon8Scene::setDungeonDoor()
{
	_dungeonDoor.x = (257 % 50) * TILESIZE;
	_dungeonDoor.y = (257 / 50) * TILESIZE - 20;
	_dungeonDoor.img = IMAGEMANAGER->findImage("dungeonDoor");
	_dungeonDoor.count = 0;
	
	KEYANIMANAGER->addDefaultFrameAnimation("closeDungeon", "dungeonDoor", 10, false, false, closeFunction,this);
	_dungeonDoor.ani = KEYANIMANAGER->findAnimation("closeDungeon");
}

void dungeon8Scene::closeFunction(void* obj)
{
	if (_dungeonNum == 7)
	{
		if (_floorNum < 3)
		{
			dungeon8Scene* c = (dungeon8Scene*)obj;
			vector<string> vStr = TXTDATA->txtLoad("random.txt");
			vStr[c->_randNum - 1] = "T";
			TXTDATA->txtSave("random.txt", vStr);
			c->_randMap1 = new RandomDungeon1;
			c->_randMap1->init();
		}
		else if (_floorNum == 3)
			SCENEMANAGER->changeScene("마을");
	}
}


/*void dungeon8Scene::setMonster()
{
	//소
	setCow(415 % _temp, 415 / _temp);

	//큰갈박
	setBigRedBat(114 % _temp, 114 / _temp);

	//음표요정
	setMusicAngel(104 % _temp, 104 / _temp);

	//큰칼뼈
	int id[3][2];
	id[0][0] = 408 % _temp, id[0][1] = 408 / _temp;
	id[1][0] = 409 % _temp, id[1][1] = 409 / _temp;
	id[2][0] = 410 % _temp, id[2][1] = 410 / _temp;
	for (int i = 0; i < 3; i++)
	{
		setBigBone(id[i][0], id[i][1], i);
	}

	//개뼈
	setDogBone(410 % _temp, 410 / _temp);

	//작갈박
	setRedBat(209 % _temp, 209 / _temp);

	//작보박
	setBat(208 % _temp, 208 / _temp);
}*/
