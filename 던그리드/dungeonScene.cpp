#include "stdafx.h"
#include "dungeonScene.h"
#include "tileNode.h"
#include "Player.h"


void dungeonScene::collision()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); )
	{
		if (_player->getIsAttacking())
		{
			RECT checkRc;
			if (IntersectRect(&checkRc, &_player->getEffect()->effectCheckBox(), &(*_viEnemy)->getRect()))
			{
				(*_viEnemy)->setCurrentHp((*_viEnemy)->getCurrentHp() - 10);
			}
		}

		for (int i=0; i < _player->getPBullet()->getvPBullet().size();)
		{
			RECT temp;
			if (IntersectRect(&temp, &(*_viEnemy)->getRect(), &_player->getPBullet()->getvPBullet()[i].rc))
			{
				_player->getPBullet()->removeBullet(i);
				(*_viEnemy)->setCurrentHp((*_viEnemy)->getCurrentHp() - 10);
			}
			else
			{
				++i;
			}

		}
		if ((*_viEnemy)->getCurrentHp() <= 0)   //ÀûÀÇ HP°¡ 0ÀÌÇÏ°¡µÇ¸é)
		{
			_viEnemy = _vEnemy.erase(_viEnemy);
				//»èÁ¦!
		}
		else
		{
			++_viEnemy;
		}
	}
}

dungeonScene::dungeonScene() {}

dungeonScene::~dungeonScene() {}

HRESULT dungeonScene::init(void)
{
	_player = SCENEMANAGER->getPlayerAddressLink();
	j = 0;
	_start = _start2 = 0;
	for (int i = 0; i < 2; i++)
	{
		_bossLaserHitCount[i] = 0;
		_bossLaserHit[i] = false;
	}
	return S_OK;
}

void dungeonScene::release(void)
{ 
}

void dungeonScene::update(void)
{
	collision();

	if(_minimap != NULL)
	_minimap->setPlayerXY(((300 * _player->getPlayerX()) / (_tileX * TILESIZE)), ((150 * (_player->getPlayerY() - 80)) / (_tileY * TILESIZE)));
}

void dungeonScene::render(void)
{
	//if (KEYMANAGER->isToggleKey(VK_F3))
	{
		for (int i = (CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2) / 96; i < (CAMERAMANAGER->getCameraCenter().y + WINSIZEY / 2) / 96 + 1; ++i)
		{
			for (int j = (CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2) / 96; j < (CAMERAMANAGER->getCameraCenter().x + WINSIZEX / 2) / 96 + 1; ++j)
			{
				IMAGEMANAGER->frameRender("map", DC, _tiles[i * _temp + j].rc.left, _tiles[i * _temp + j].rc.top, _tiles[i * _temp + j].terrainFrameX, _tiles[i * _temp + j].terrainFrameY);
			}
		}

		for (int i = (CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2) / 96; i < (CAMERAMANAGER->getCameraCenter().y + WINSIZEY / 2) / 96 + 1; ++i)
		{
			for (int j = (CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2) / 96; j < (CAMERAMANAGER->getCameraCenter().x + WINSIZEX / 2) / 96 + 1; ++j)
			{
				if (_tiles[i * _temp + j].object == OBJ_NONE) continue;

				IMAGEMANAGER->frameRender("map", DC, _tiles[i * _temp + j].rc.left, _tiles[i * _temp + j].rc.top, _tiles[i * _temp + j].objFrameX, _tiles[i * _temp + j].objFrameY);
			}
		}
	}
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = (CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2) / 96; i < (CAMERAMANAGER->getCameraCenter().y + WINSIZEY / 2) / 96 + 1; ++i)
		{
			for (int j = (CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2) / 96; j < (CAMERAMANAGER->getCameraCenter().x + WINSIZEX / 2) / 96 + 1; ++j)
			{
				char str[128];
				sprintf_s(str, "%d", i * _temp + j);
				TextOut(DC, _tiles[i * _temp + j].rc.left, _tiles[i * _temp + j].rc.top, str, strlen(str));
			}
		}
	}

	for (int i = 0; i < _vDoor.size(); i++)
	{
		//Rectangle(DC, _vDoor[i].rc.left, _vDoor[i].rc.top, _vDoor[i].rc.right, _vDoor[i].rc.bottom);
		//_vDoor[i].img->frameRender(DC, _vDoor[i].rc.left, _vDoor[i].rc.top);
	}

	for (int i = 0; i < _vTorch.size(); i++)
	{
		_vTorch[i].img->aniRender(DC, _vTorch[i].x, _vTorch[i].y, _vTorch[i].ani);
		//_vTorch[0].img->render(DC, _vTorch[0].x, _vTorch[0].y);
	}

	portalRender();


	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->render();
	}

	//	RECT rc;
	//	rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);
	//	Rectangle(DC, rc.left, rc.top, rc.right, rc.bottom);
		//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && PtInRect(&rc, getMemDCPoint()))
		//{
		//	_mapValue[_dungeonNum] = "T";
		//}
	char str[128];
	sprintf_s(str, "¸Ê : %d, °ñµå : %d", _dungeonNum, _player->getGold());
	TextOut(DC, 100, 100, str, strlen(str));
	_count++;
	_enemyBullet->render();
	for (int i = 0; i < 20; i++)
	{
		_bigRadBatBullet[i]->render();
	}

	_bigBatBullet->render();
	_bigRadBullet->render();

	doorRender();
	if(_minimap != NULL)
		_minimap->render();
}

void dungeonScene::doorInit(void)
{
}

void dungeonScene::torchInit(int x, int y)
{
	torch torch;
	torch.img = IMAGEMANAGER->findImage("torch");
	torch.ani = KEYANIMANAGER->findAnimation("torchAni");
	torch.x = x * TILESIZE;
	torch.y = y * TILESIZE;
	torch.ani->start();
	_vTorch.push_back(torch);
}

void dungeonScene::portalInit(float x, float y)
{
	Portal portal;
	portal.x = x * TILESIZE;
	portal.y = y * TILESIZE;
	portal.img = IMAGEMANAGER->findImage("portal");
	portal.frameX = 8;
	portal.frameY = portal.count = 0;
	_vPortal.push_back(portal);
}



void dungeonScene::setRandMapNum(void)
{
}


void dungeonScene::mapload()
{
	HANDLE   file;
	DWORD   load;

	ZeroMemory(&_tiles, sizeof(tagTile) * TILEX * TILEY);

	file = CreateFile(_mapName.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &load, NULL);

	//setMinimap();
	//ÈñÁø´©³ª ¹Ù²² ¾ø´Ù ¿©À¹½Ã /
	for (int i = 0; i < TILEX; ++i)
	{
		for (int j = 0; j < TILEY; ++j)
		{
			//ºüÁø°Å Ã³¸® 
			if (_tiles[i * TILEX + j].terrainFrameX == 1 && _tiles[i * TILEX + j].terrainFrameY == 3) _tiles[i* TILEX + j].object = OBJ_CULUMN;
			//ÅàˆÔ 
			if (_tiles[i * TILEX + j].objFrameX == 0 && _tiles[i * TILEX + j].objFrameY == 2) _tiles[i* TILEX + j].object = OBJ_CEILING;
			if (_tiles[i * TILEX + j].objFrameX == 1 && _tiles[i * TILEX + j].objFrameY == 2) _tiles[i* TILEX + j].object = OBJ_CEILING;
			if (_tiles[i * TILEX + j].objFrameX == 2 && _tiles[i * TILEX + j].objFrameY == 2) _tiles[i* TILEX + j].object = OBJ_CEILING;
			if (_tiles[i * TILEX + j].objFrameX == 0 && _tiles[i * TILEX + j].objFrameY == 6) _tiles[i* TILEX + j].object = OBJ_CEILING;
			if (_tiles[i * TILEX + j].objFrameX == 1 && _tiles[i * TILEX + j].objFrameY == 6) _tiles[i* TILEX + j].object = OBJ_CEILING;
			if (_tiles[i * TILEX + j].objFrameX == 2 && _tiles[i * TILEX + j].objFrameY == 6) _tiles[i* TILEX + j].object = OBJ_CEILING;

			////ÎÃ Èñ Áø ÎÃ Èñ Áø ÎÃ Èñ Áø ÎÃ Èñ Áø ÎÃ Èñ Áø ÎÃ Èñ Áø ÎÃ Èñ Áø ÎÃ Èñ Áø ÎÃ Èñ Áø ÎÃ Èñ Áø ÎÃ Èñ Áø ÎÃ Èñ Áø ÎÃ Èñ Áø ÎÃ Èñ Áø ÎÃ Èñ Áø ÎÃ Èñ Áø 
			if (_tiles[i* TILEX + j].objFrameX == 8 && _tiles[i* TILEX + j].objFrameY == 0) _tiles[i* TILEX + j].object = OBJ_DIAGONAL_LEFT;
			if (_tiles[i* TILEX + j].objFrameX == 9 && _tiles[i* TILEX + j].objFrameY == 0) _tiles[i* TILEX + j].object = OBJ_DIAGONAL_RIGHT;
			if (_tiles[i* TILEX + j].objFrameX == 11 && _tiles[i* TILEX + j].objFrameY == 0) _tiles[i* TILEX + j].object = OBJ_DIAGONAL_RIGHT;
			if (_tiles[i* TILEX + j].objFrameX == 11 && _tiles[i* TILEX + j].objFrameY == 21) _tiles[i* TILEX + j].object = OBJ_DIAGONAL;
			if (_tiles[i* TILEX + j].objFrameX == 13 && _tiles[i* TILEX + j].objFrameY == 0) _tiles[i* TILEX + j].object = OBJ_DIAGONAL_LEFT;
			//	if (_tiles[i* TILEX + j].objFrameX == 5 && _tiles[i* TILEX + j].objFrameY == 3) _tiles[i* TILEX + j].object  = OBJ_DIAGONAL;
			if (_tiles[i* TILEX + j].objFrameX == 7 && _tiles[i* TILEX + j].objFrameY == 3) _tiles[i* TILEX + j].object = OBJ_DIAGONAL_RIGHT;
			if (_tiles[i* TILEX + j].objFrameX == 8 && _tiles[i* TILEX + j].objFrameY == 3) _tiles[i* TILEX + j].object = OBJ_DIAGONAL_LEFT;
			if (_tiles[i* TILEX + j].objFrameX == 10 && _tiles[i* TILEX + j].objFrameY == 3) _tiles[i* TILEX + j].object = OBJ_DIAGONAL;
		}
	}

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tiles[i].terrainFrameX == 17 && _tiles[i].terrainFrameY == 1)  _tiles[i].object = OBJ_CULUMN;
		if (_tiles[i].terrainFrameX == 16 && _tiles[i].terrainFrameY == 1)  _tiles[i].object = OBJ_CULUMN;
		if (_tiles[i].terrainFrameX == 12 && _tiles[i].terrainFrameY == 25) _tiles[i].object = OBJ_CULUMN;

	}
	CloseHandle(file);

	//setMinimap();

	_enemyBullet = new Bullet;
	_enemyBullet->init(3000);

	for (int i = 0; i < 20; i++)
	{
		_bigRadBatBullet[i] = new Bullet2;
		_bigRadBatBullet[i]->init(1000);
	}


	_bigBatBullet = new Bullet;
	_bigBatBullet->init(1000);

	_bigRadBullet = new Bullet2;
	_bigRadBullet->init(2000);

}

void dungeonScene::setMinimap()
{
	_minimap = new minimap;
	_minimap->init(true);

	image* tempImg;
	/*tempImg = IMAGEMANAGER->addImage("ÅÛÇª", _tileX*TILESIZE, _tileY * TILESIZE);
	PatBlt(tempImg->getMemDC(), 0, 0, _tileX * TILESIZE, _tileY * TILESIZE, BLACKNESS);*/

	tempImg = IMAGEMANAGER->addImage("ÅÛÇª", TILEX*TILESIZE, TILEY * TILESIZE);
	PatBlt(tempImg->getMemDC(), 0, 0, TILEX * TILESIZE, TILEY * TILESIZE, BLACKNESS);


	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			if (_tiles[i * TILEX + j].object == OBJ_NONE) continue;
			IMAGEMANAGER->frameRender("map", tempImg->getMemDC(), _tiles[i * TILEX + j].rc.left, _tiles[i * TILEX + j].rc.top, _tiles[i * TILEX + j].objFrameX, _tiles[i * TILEX + j].objFrameY);
			//IMAGEMANAGER->frameRender("map", tempImg->getMemDC(), _tiles[i * _temp + j].rc.left, _tiles[i * _temp + j].rc.top, _tiles[i * _temp + j].terrainFrameX, _tiles[i * _temp + j].terrainFrameY);
		}
	}
	_minimap->setMinimap(tempImg->getMemDC());
	_minimap->setPlayerXY(((300 * _player->getPlayerX()) / (_tileX * TILESIZE)), ((150 * _player->getPlayerY()) / (_tileY * TILESIZE)));
	if (_vPortal.size() > 0)
	{
		_minimap->setPortalXY(((300 * _vPortal[0].x) / (_tileX*TILESIZE)), ((150 * (_vPortal[0].y - 50)) / (_tileY*TILESIZE)));
	}
}

void dungeonScene::setDoorMinimap()
{
	for (int i = 0; i < _vDoor.size(); i++)
	{
		if (_vDoor[i].dir == DOOR_UPDOWN)
			_minimap->setDoorXY((300*_vDoor[i].x)/(_tileX*TILESIZE), (150*_vDoor[i].y)/(_tileY*TILESIZE), false);
		else
			_minimap->setDoorXY((300 * _vDoor[i].x) / (_tileX*TILESIZE), (150 * _vDoor[i].y) / (_tileY*TILESIZE), true);
	}
}

void dungeonScene::setCamera(void)
{
	CAMERAMANAGER->setCameraCenter(PointMake(0, 0));
}

void dungeonScene::selectSize(int idx)
{
	if (idx == 0)
		_temp = 80;
	if (idx == 1)
		_temp = 29;
	if (idx == 2)
		_temp = 29;
	if (idx == 3)
		_temp = 100;
	if (idx == 4)
		_temp = 30;
	if (idx == 5)
		_temp = 25;
	if (idx == 6) //ÀÌ»ó...
		_temp = 50;
	if (idx == 7)
		_temp = 25;
	if (idx == 8)
		_temp = 20;
	if (idx == 9)
		_temp = 50;
	if (idx == 10)
		_temp = 50;
	if (idx == 11)
		_temp = 25;
}

void dungeonScene::chooseMap(int idx)
{
	if (idx == 0)
		_mapName = "map/townmap(80x25).map";
	if (idx == 1)
		_mapName = "map/Dungeon1(28x11).map";
	if (idx == 2)
		_mapName = "map/Dungeon2(28x13).map";
	if (idx == 3)
		_mapName = "map/Dungeon3(20x13).map";
	if (idx == 4)
		_mapName = "map/Dungeon4(29X16).map";
	if (idx == 5)
		_mapName = "map/Dungeon5(25x16).map";
	if (idx == 6)
		_mapName = "map/Dungeon6(49x28).map";
	if (idx == 7)
		_mapName = "map/Dungeon7(25x30).map";
	if (idx == 8)
		_mapName = "map/Dungeon8(20x39).map";
	if (idx == 9)
		_mapName = "map/Dungeon9(20x11).map";
	if (idx == 10)
		_mapName = "map/bossMap(21,18).map";
	if (idx == 11)
		_mapName = "map/weaponsStore(25x15).map";

	_tileX = TILEVALUE[idx][0], _tileY = TILEVALUE[idx][1];
}

//¸ó½ºÅÍ »ý¼º ÇÔ¼ö
//°³»À
void dungeonScene::setDogBone(int idX, int idY)
{
	DogBone* dogBone;
	dogBone = new DogBone;
	float x = TILESIZE * idX;
	float y = TILESIZE * idY;
	y += TILESIZE / 2 + 15;
	dogBone->init(x, y);
	dogBone->setPlayerAddressLink(_player);
	_vEnemy.push_back(dogBone);
}
//Å«Ä®»À
void dungeonScene::setBigBone(int idX, int idY, int index)
{
	BigBone* bigBone;
	bigBone = new BigBone;
	float x = TILESIZE * idX;
	float y = TILESIZE * idY;
	y -= 20;
	bigBone->init(x, y, index);
	bigBone->setPlayerAddressLink(_player);
	_vEnemy.push_back(bigBone);
}
//È°ÀïÀÌ
void dungeonScene::setArrow(int idX, int idY)
{
	Arrow* arrow;
	arrow = new Arrow;
	float x = TILESIZE * idX;
	float y = TILESIZE * idY;
	y += 15;
	arrow->init(x, y);
	arrow->setPlayerAddressLink(_player);
	_vEnemy.push_back(arrow);
}
//ÀÛº¸¹Ú
void dungeonScene::setBat(int idX, int idY)
{
	Bat* bat;
	bat = new Bat;
	float x = TILESIZE * idX;
	float y = TILESIZE * idY;
	bat->init(x, y);
	bat->setPlayerAddressLink(_player);
	_vEnemy.push_back(bat);
}
//ÀÛ»¡¹Ú
void dungeonScene::setRedBat(int idX, int idY)
{
	RedBat* redBat;
	redBat = new RedBat;
	float x = TILESIZE * idX;
	float y = TILESIZE * idY;
	redBat->init(x, y);
	redBat->setPlayerAddressLink(_player);
	_vEnemy.push_back(redBat);
}

void dungeonScene::setBigBat(int idX, int idY)
{
	_bigbat = new BigBat;
	float x = TILESIZE * idX;
	float y = TILESIZE * idY;
	_bigbat->init(x, y);
	_bigbat->setPlayerAddressLink(_player);
	_vEnemy.push_back(_bigbat);
}

void dungeonScene::setBigRedBat(int idX, int idY)
{
	_bigRedBat = new BigRedBat;
	float x = TILESIZE * idX;
	float y = TILESIZE * idY;
	_bigRedBat->init(x, y);
	_bigRedBat->setPlayerAddressLink(_player);
	_vEnemy.push_back(_bigRedBat);
}

void dungeonScene::setMusicAngel(int idX, int idY)
{
	_musicAngel = new MusicAngel;
	float x = TILESIZE * idX;
	float y = TILESIZE * idY;
	_musicAngel->init(x, y);
	_musicAngel->setPlayerAddressLink(_player);
	_vEnemy.push_back(_musicAngel);
}

void dungeonScene::setCow(int idX, int idY)
{
	Cow* cow;
	cow = new Cow;
	float x = TILESIZE * idX;
	float y = TILESIZE * idY;
	x += 50;
	y -= 15;
	cow->init(x, y);
	cow->setPlayerAddressLink(_player);
	_vEnemy.push_back(cow);
}

void dungeonScene::setBoss()
{
	_boss = new Boss2;
	_boss->init();
	_boss->setPlayerAddressLink(_player);
	_vEnemy.push_back(_boss);
}

void dungeonScene::nextTest()
{
	//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _mapValue[_dungeonNum] == "T")
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _vDoor.size(); i++)
		{
			if (PtInRect(&_vDoor[i].rc, getMemDCPoint()))
			{
				string str = "´øÀü¸Ê";
				char temp[128] = "";
				str += itoa(_route[i], temp, 10);
				save();
				SCENEMANAGER->changeScene(str);
			}
		}
	}
}

void dungeonScene::load()
{
	vector<string> vStr = TXTDATA->txtLoad("infoDungeon.txt");
	if (vStr.size() != 0)
	{
		_randNum = atoi(vStr[0].c_str());
		for (int i = 0; i < 11; i++)
		{
			_mapValue[i] = vStr[i + 1];
		}
	}
}

void dungeonScene::save()
{
	vector<string> vStr;
	char str[128];
	vStr.push_back(itoa(_randNum, str, 10));
	for (int i = 0; i < 11; i++)
	{
		vStr.push_back(_mapValue[i]);
	}

	TXTDATA->txtSave("infoDungeon.txt", vStr);
}




void dungeonScene::setDoor()
{
	for (int i = 0; i < _vDoor.size(); i++)
	{
		_vDoor[i].state = DOOR_OPEN;

		if (_vDoor[i].dir == DOOR_RIGHT)
		{
			_vDoor[i].frameX = 3, _vDoor[i].frameY = 0;
		}
		else
		{
			_vDoor[i].frameX = _vDoor[i].frameY = 0;
		}
	}
}

void dungeonScene::doorRender()
{
	for (int i = 0; i < _vDoor.size(); i++)
	{
		_vDoor[i].count++;
		if (!(_vDoor[i].count % 10))
		{
			if (_vDoor[i].state == DOOR_OPEN)
			{
				if (_vDoor[i].dir == DOOR_RIGHT)
				{
					if (_vDoor[i].frameY == 5)
						_vDoor[i].state = DOOR_IDLE;
					else
						_vDoor[i].frameY++;
				}
				if (_vDoor[i].dir == DOOR_LEFT)
				{
					if (_vDoor[i].frameY == 5)
						_vDoor[i].state = DOOR_IDLE;
					else
						_vDoor[i].frameY++;
				}
				if (_vDoor[i].dir == DOOR_UPDOWN)
				{
					if (_vDoor[i].frameX == 5)
						_vDoor[i].state = DOOR_IDLE;
					else
						_vDoor[i].frameX++;
				}
			}
			else if (_vDoor[i].state == DOOR_IDLE)
			{
				if (_vDoor[i].dir == DOOR_RIGHT)
				{
					if (_vDoor[i].frameX == 3 && _vDoor[i].frameY == 5)
						_vDoor[i].frameX = 2, _vDoor[i].frameY = 0;
					else if (_vDoor[i].frameX == 2 && _vDoor[i].frameY == 5)
						_vDoor[i].frameX = 1, _vDoor[i].frameY = 0;
					else if (_vDoor[i].frameX == 1 && _vDoor[i].frameY == 5)
						_vDoor[i].frameX = 3, _vDoor[i].frameY = 5;
					else
						_vDoor[i].frameY++;
				}
				else if (_vDoor[i].dir == DOOR_LEFT)
				{
					if (_vDoor[i].frameX == 0 && _vDoor[i].frameY == 5)
						_vDoor[i].frameX = 1, _vDoor[i].frameY = 0;
					else if (_vDoor[i].frameX == 1 && _vDoor[i].frameY == 5)
						_vDoor[i].frameX = 2, _vDoor[i].frameY = 0;
					else if (_vDoor[i].frameX == 2 && _vDoor[i].frameY == 5)
						_vDoor[i].frameX = 1, _vDoor[i].frameY = 5;
					else
						_vDoor[i].frameY++;
				}
				else if (_vDoor[i].dir == DOOR_UPDOWN)
				{
					if (_vDoor[i].frameY == 0 && _vDoor[i].frameX == 5)
						_vDoor[i].frameY = 1, _vDoor[i].frameX = 0;
					else if (_vDoor[i].frameY == 1 && _vDoor[i].frameX == 5)
						_vDoor[i].frameY = 2, _vDoor[i].frameX = 0;
					else if (_vDoor[i].frameY == 2 && _vDoor[i].frameX == 5)
						_vDoor[i].frameY = 1, _vDoor[i].frameX = 5;
					else
						_vDoor[i].frameX++;
				}
			}
			else if (_vDoor[i].state == DOOR_CLOSE)
			{
				if (_vDoor[i].dir == DOOR_RIGHT)
				{
					if (_vDoor[i].frameY < _vDoor[i].img->getMaxFrameY())
						_vDoor[i].frameY++;
				}
				if (_vDoor[i].dir == DOOR_LEFT)
				{
					if (_vDoor[i].frameY < _vDoor[i].img->getMaxFrameY())
						_vDoor[i].frameY++;
				}
				if (_vDoor[i].dir == DOOR_UPDOWN)
				{
					if (_vDoor[i].frameX < _vDoor[i].img->getMaxFrameX())
						_vDoor[i].frameX++;
				}
			}
		}
		_vDoor[i].img->frameRender(DC, _vDoor[i].rc.left, _vDoor[i].rc.top, _vDoor[i].frameX, _vDoor[i].frameY);
		if (_mapValue[_dungeonNum] == "T" && _vDoor[i].state != DOOR_CLOSE)
		{
			if (_vDoor[i].dir == DOOR_RIGHT)
			{
				if (_vDoor[i].frameX == 1 && _vDoor[i].frameY == 5)
				{
					_vDoor[i].state = DOOR_CLOSE;
					_vDoor[i].frameX = 0, _vDoor[i].frameY = 0;
				}
			}
			if (_vDoor[i].dir == DOOR_LEFT)
			{
				if (_vDoor[i].frameX == 2 && _vDoor[i].frameY == 5)
				{
					_vDoor[i].state = DOOR_CLOSE;
					_vDoor[i].frameX = 3, _vDoor[i].frameY = 0;
				}
			}
			if (_vDoor[i].dir == DOOR_UPDOWN)
			{
				if (_vDoor[i].frameY == 2 && _vDoor[i].frameX == 5)
				{
					_vDoor[i].state = DOOR_CLOSE;
					_vDoor[i].frameY = 3, _vDoor[i].frameX = 0;
				}
			}
		}
	}
}

void dungeonScene::portalRender()
{
	for (int i = 0; i < _vPortal.size(); i++)
	{
		_vPortal[i].img->frameRender(DC, _vPortal[i].x, _vPortal[i].y, _vPortal[i].frameX, _vPortal[i].frameY);
		_vPortal[i].count++;
		if (!(_vPortal[i].count % 5))
		{

			if (_vPortal[i].frameY == 0)
			{
				if (_vPortal[i].frameX == 0) _vPortal[i].frameY = 1;
				else _vPortal[i].frameX--;
			}
			else if (!(_vPortal[i].count % 10))
			{
				_vPortal[i].count = 0;
				if (_vPortal[i].frameX >= _vPortal[i].img->getMaxFrameX())
					_vPortal[i].frameX = 0;
				else
					_vPortal[i].frameX++;
			}
		}
	}
}

void dungeonScene::musicAngelBulletCollision()
{
	for (int i = 0; i < _enemyBullet->getVBullet().size(); i++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_enemyBullet->getVBullet()[i].rc, &_player->getPlayerRect()))
		{
			_player->hitDamage(1.7f);
			EFFECTMANAGER->play("bansheeBigBullet", (_player->getPlayerRect().right + _player->getPlayerRect().left) / 2, (_player->getPlayerRect().bottom + _player->getPlayerRect().top) / 2);
			_enemyBullet->removeBullet(i);
			break;
		}
	}
}

void dungeonScene::bossBulletCollision()
{
	for (int i = 0; i < _enemyBullet->getVBullet().size(); i++)
	{
		RECT temp;
		//ÃÑ¾Ë Ãæµ¹
		//if (_enemyBullet->getFrameXY(_enemyBullet->getVBullet()[i].frameXY) == WIDTH)
		if (_enemyBullet->getFrameXY(i) == WIDTH)
		{
			if (IntersectRect(&temp, &_enemyBullet->getVBullet()[i].rc, &_player->getPlayerRect()))
			{
				//_player->hitDamage(3.1f);
				EFFECTMANAGER->play("bossCollisionBullet", (_player->getPlayerRect().right + _player->getPlayerRect().left) / 2, (_player->getPlayerRect().bottom + _player->getPlayerRect().top) / 2);
				_enemyBullet->removeBullet(i);
				break;
			}
		}
	}

	for (int i = 0; i < _enemyBullet->getVBullet().size(); i++)
	{
		//·¹ÀÌÁ® Ãæµ¹
		//if (_enemyBullet->getFrameXY(_enemyBullet->getVBullet()[i].frameXY) == HEIGHT)
		if (_enemyBullet->getFrameXY(i) == HEIGHT)
		{
			RECT temp;
			if (_boss->getLeftDirection() == LEFT_LASER_OFF)
			{
				if (IntersectRect(&temp, &_enemyBullet->getVBullet()[i].rc, &_player->getPlayerRect()))
				{
					if (!_bossLaserHit[0])
					{
						//_player->hitDamage(2.6f);
						EFFECTMANAGER->play("bossCollisionBullet", (_player->getPlayerRect().right + _player->getPlayerRect().left) / 2, (_player->getPlayerRect().bottom + _player->getPlayerRect().top) / 2);
						_bossLaserHit[0] = true;
						_bossLaserHitCount[0] = 0;
					}
					_bossLaserHitCount[0]++;
					if (!(_bossLaserHitCount[0] % 120) && _bossLaserHit[0])
					{
						_bossLaserHit[0] = false;
					}
				}
			}
			if (_boss->getRightDirection() == RIGHT_LASER_OFF)
			{
				if (IntersectRect(&temp, &_enemyBullet->getVBullet()[i].rc, &_player->getPlayerRect()))
				{
					if (!_bossLaserHit[1])
					{
						//_player->hitDamage(2.6f);
						EFFECTMANAGER->play("bossCollisionBullet", (_player->getPlayerRect().right + _player->getPlayerRect().left) / 2, (_player->getPlayerRect().bottom + _player->getPlayerRect().top) / 2);
						_bossLaserHit[1] = true;
						_bossLaserHitCount[1] = 0;
					}
					_bossLaserHitCount[1]++;
					if (!(_bossLaserHitCount[1] % 120) && _bossLaserHit[1])
					{
						_bossLaserHit[1] = false;
					}
				}
			}
		}
	}
}

//ÃÑ¾Ë »ý¼º ÇÔ¼ö
//À½Ç¥¿äÁ¤ ÃÑ¾Ë
void dungeonScene::MusicAngelBulletFire()
{
	musicAngelBulletCollision();
	if (!(_count % 200))
	{
		for (int i = 0; i < 12; i++)
		{
			float angle = (PI2 / 12)*i;
			_enemyBullet->bulletFire("bansheeNormalBullet", _musicAngel->getX(), _musicAngel->getY(), angle, 5.0f, 500, true);
		}
		_count = 0;
	}

}

//º¸½ºÃÑ¾Ë
void dungeonScene::BossBulletFire()
{
	bossBulletCollision();
	//==========================================================
	//						º¸½º ÃÑ¾Ë
	//==========================================================
	//ÀÔ ÃÑ¾Ë ¸ÕÀú ÇÏ°ÚÀ½.
	//ÀÔ ÃÑ¾ËÀº ¸Ó¸®Åë ¿­¸®´Â ¼ø°£¿¡¸¸ ÇÔ
	static float angle = 0;
	static bool	isCheck = false;		// ÀÌ°Å °¡Áö°í ¾Þ±Û°ª + OR - ½ÃÅ´

	if (_boss->getHeadX() < getMemDCPoint().x) isCheck = true;   // ¿ä±â ¸¶¿ì½º ÁÂÇ¥¸¦ ÇÃ·¹ÀÌ¾î X ÁÂÇ¥·Î ¹Ù²Ù¸é µË´Ï´Ù.
	else isCheck = false;

	//==========================================================
	//					º¸½º ¿ÞÂÊ ·¹ÀÌÁ®
	//==========================================================

	if (_boss->getLeftDirection() == LEFT_LASER_ON)
	{
		_enemyBullet->bulletFire("bossLaser", _boss->getLeftX() + 800, _boss->getLeftY(), 0, 0.0f, 1000, true, HEIGHT);
		_boss->setLeftDirection(LEFT_LASER_OFF);
	}

	//==========================================================
	//					º¸½º ¿À¸¥ÂÊ ·¹ÀÌÁ®
	//==========================================================

	if (_boss->getRightDirection() == RIGHT_LASER_ON)
	{
		_enemyBullet->bulletFire("bossRLaser", _boss->getRightX() - 850, _boss->getRightY(), 0, 0.0f, 1000, true, HEIGHT); //¿À¸¥¼Õ ·¹ÀÌÁ®
		_boss->setRightDirection(RIGHT_LASER_OFF);
	}

	if (!_boss->isAttack()) return;

	//¿ä±â
	if (!isCheck) angle += 0.02; //ÃÑ¾Ë µ¹¾Æ°¡´Â ¼Óµµ Á¶Àý
	else angle -= 0.02;

	if (!(_count % 7)) //ÃÑ¾Ë ³ª°¡´Â ¼Óµµ Á¶Àý
	{
		for (int i = 0; i < 4; i++)
		{
			angle += (i * PI / 2);
			//float angle = i * PI / 2;
			_enemyBullet->bulletFire("bossBullet", _boss->getHeadX() + 50, _boss->getHeadY() + 120, angle, 9.0f, 1000, true); //9.0f¶û À§¿¡ angle, count ·Î Á¶ÀýÇØ¼­ ÃÑ¾Ë Á¶Àý °¡´É
		}
		_count = 0;
	}
}

void dungeonScene::bigbatbulletFire()
{
	_count2++;
	if (_bigbat->getisAtteck() == true)
	{
		if (_count2 % 10 == 0 && _count2 > 170)
		{
			for (int i = 0; i < 3; i++)
			{
				float angle = -(PI2 / 9) * i;
				_bigBatBullet->bulletFire("fatherBatBullet2", _bigbat->getX() + 50, _bigbat->getY() + 10, angle, 5.0f, 500);
			}
			_start2 = 1;
		}
		if (_count2 > 200)
		{
			_count2 = 0;
			_bigbat->setisAtteck(false);
		}
	}
}


void dungeonScene::bigRadbatbulletFire()
{
	_count3++;
	if(!(_count3 % 5) && _count3 > 0)
	{
		if (_bigRedBat->getisAtteck2() == true)
		{
			if (j <= 20)
			{
				if (j == 20)
					_start = 1;
				else
				{
					if (j == 0)
						_start = 0;
					float angle2 = PI2 / 20 * j;
					float bulletX = _bigRedBat->getX() + 150;
					float bulletY = _bigRedBat->getY() + 50;
					_bigRadBatBullet[j]->bulletFire("fatherBatBullet2", bulletX + cosf(angle2) * 150, _bigRedBat->getY() + -sinf(angle2) * 150, angle2, 5.0f, 500);
					j++;
				}
			}

			if (j == 20)
			{
				bool fin = false;
				for (int i = 0; i < MAX_BULLET; i++)
				{
					if (_bigRadBatBullet[i]->getVBullet().size() != 0)
					{
						fin = true;
						break;
					}
				}
				if (!fin)
				{
					_start = 0;
					j = 0;
					_count3 = -500;
					_bigRedBat->setisAtteck2(false);
				}
			}
		}
	}
}