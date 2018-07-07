#include "stdafx.h"
#include "dungeonScene.h"
#include "tileNode.h"


dungeonScene::dungeonScene() {}

dungeonScene::~dungeonScene() {}

HRESULT dungeonScene::init(void)
{
	return S_OK;
}

void dungeonScene::release(void)
{
}

void dungeonScene::update(void)
{
	//KEYANIMANAGER->update();
}

void dungeonScene::render(void)
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

	for (int i = 0; i < _door.size(); i++)
	{
		//Rectangle(DC, _door[i].rc.left, _door[i].rc.top, _door[i].rc.right, _door[i].rc.bottom);
		//_door[i].img->frameRender(DC, _door[i].rc.left, _door[i].rc.top);
	}

	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->render();
	}

	RECT rc;
	rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);
	Rectangle(DC, rc.left, rc.top, rc.right, rc.bottom);
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && PtInRect(&rc, getMemDCPoint()))
	{
		_mapValue[_dungeonNum] = "T";
	}

	doorRender();
}

void dungeonScene::mapload()
{
	HANDLE   file;
	DWORD   load;
	ZeroMemory(&_tiles, sizeof(tagTile) * TILEX * TILEY);

	file = CreateFile(_mapName.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &load, NULL);

	CloseHandle(file);
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

//°³»À
void dungeonScene::setDogBone(int idX, int idY)
{
	DogBone* dogBone;
	dogBone = new DogBone;
	float x = TILESIZE * idX;
	float y = TILESIZE * idY;
	y += TILESIZE / 2 + 15;
	dogBone->init(x, y);
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
	_vEnemy.push_back(redBat);
}

void dungeonScene::setBigBat(int idX, int idY)
{
	BigBat* bigBat;
	bigBat = new BigBat;
	float x = TILESIZE * idX;
	float y = TILESIZE * idY;
	bigBat->init(x, y);
	_vEnemy.push_back(bigBat);
}

void dungeonScene::setBigRedBat(int idX, int idY)
{
	BigRedBat* bigRedBat;
	bigRedBat = new BigRedBat;
	float x = TILESIZE * idX;
	float y = TILESIZE * idY;
	bigRedBat->init(x, y);
	_vEnemy.push_back(bigRedBat);
}

void dungeonScene::setMusicAngel(int idX, int idY)
{
	MusicAngel* musicAngel;
	musicAngel = new MusicAngel;
	float x = TILESIZE * idX;
	float y = TILESIZE * idY;
	musicAngel->init(x, y);
	_vEnemy.push_back(musicAngel);
}

void dungeonScene::setCow(int idX, int idY)
{
	Cow* cow;
	cow = new Cow;
	float x = TILESIZE * idX;
	float y = TILESIZE * idY;
	cow->init(x, y);
	_vEnemy.push_back(cow);
}

void dungeonScene::setBoss()
{
	Boss2* boss;
	boss = new Boss2;
	boss->init();
	_vEnemy.push_back(boss);
}

void dungeonScene::nextTest()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _mapValue[_dungeonNum] == "T")
	//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _door.size(); i++)
		{
			if (PtInRect(&_door[i].rc, getMemDCPoint()))
			{
				string str = "´øÀü¸Ê";
				char temp[128];
				str += itoa(_route[i],temp,10);
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
	vStr.push_back(itoa(_randNum,str,10));
	for (int i = 0; i < 11; i++)
	{
		vStr.push_back(_mapValue[i]);
	}

	TXTDATA->txtSave("infoDungeon.txt", vStr);
}

void dungeonScene::setDoor()
{
	for (int i = 0; i < _door.size(); i++)
	{
		_door[i].state = DOOR_OPEN;

		if (_door[i].dir == DOOR_RIGHT)
		{
			_door[i].frameX = 3, _door[i].frameY = 0;
		}
		else
		{
			_door[i].frameX = _door[i].frameY = 0;
		}
	}
}

void dungeonScene::doorRender()
{
	for (int i = 0; i < _door.size(); i++)
	{
		_door[i].count++;
		if (!(_door[i].count % 10))
		{
			if (_door[i].state == DOOR_OPEN)
			{
				if (_door[i].dir == DOOR_RIGHT)
				{
					if (_door[i].frameY == 5)
						_door[i].state = DOOR_IDLE;
					else
						_door[i].frameY++;
				}
				if (_door[i].dir == DOOR_LEFT)
				{
					if (_door[i].frameY == 5)
						_door[i].state = DOOR_IDLE;
					else
						_door[i].frameY++;
				}
				if (_door[i].dir == DOOR_UPDOWN)
				{
					if (_door[i].frameX == 5)
						_door[i].state = DOOR_IDLE;
					else
						_door[i].frameX++;
				}
			}
			else if (_door[i].state == DOOR_IDLE)
			{
				if (_door[i].dir == DOOR_RIGHT)
				{
					if (_door[i].frameX == 3 && _door[i].frameY == 5)
						_door[i].frameX = 2, _door[i].frameY = 0;
					else if (_door[i].frameX == 2 && _door[i].frameY == 5)
						_door[i].frameX = 1, _door[i].frameY = 0;
					else if (_door[i].frameX == 1 && _door[i].frameY == 5)
						_door[i].frameX = 3, _door[i].frameY = 5;
					else
						_door[i].frameY++;
				}
				else if (_door[i].dir == DOOR_LEFT)
				{
					if (_door[i].frameX == 0 && _door[i].frameY == 5)
						_door[i].frameX = 1, _door[i].frameY = 0;
					else if (_door[i].frameX == 1 && _door[i].frameY == 5)
						_door[i].frameX = 2, _door[i].frameY = 0;
					else if (_door[i].frameX == 2 && _door[i].frameY == 5)
						_door[i].frameX = 1, _door[i].frameY = 5;
					else
						_door[i].frameY++;
				}
				else if (_door[i].dir == DOOR_UPDOWN)
				{
					if (_door[i].frameY == 0 && _door[i].frameX == 5)
						_door[i].frameY = 1, _door[i].frameX = 0;
					else if (_door[i].frameY == 1 && _door[i].frameX == 5)
						_door[i].frameY = 2, _door[i].frameX = 0;
					else if (_door[i].frameY == 2 && _door[i].frameX == 5)
						_door[i].frameY = 1, _door[i].frameX = 5;
					else
						_door[i].frameX++;
				}
			}
			else if (_door[i].state == DOOR_CLOSE)
			{
				if (_door[i].dir == DOOR_RIGHT)
				{
					if (_door[i].frameY < _door[i].img->getMaxFrameY())
						_door[i].frameY++;
				}
				if (_door[i].dir == DOOR_LEFT)
				{
					if (_door[i].frameY < _door[i].img->getMaxFrameY())
						_door[i].frameY++;
				}
				if (_door[i].dir == DOOR_UPDOWN)
				{
					if (_door[i].frameX < _door[i].img->getMaxFrameX())
						_door[i].frameX++;
				}
			}
		}
		_door[i].img->frameRender(DC, _door[i].rc.left, _door[i].rc.top, _door[i].frameX, _door[i].frameY);
		if (_mapValue[_dungeonNum] == "T" && _door[i].state != DOOR_CLOSE)
		{
			if (_door[i].dir == DOOR_RIGHT)
			{
				if (_door[i].frameX == 1 && _door[i].frameY == 5)
				{
					_door[i].state = DOOR_CLOSE;
					_door[i].frameX = 0, _door[i].frameY = 0;
				}
			}
			if (_door[i].dir == DOOR_LEFT)
			{
				if (_door[i].frameX == 2 && _door[i].frameY == 5)
				{
					_door[i].state = DOOR_CLOSE;
					_door[i].frameX = 3, _door[i].frameY = 0;
				}
			}
			if (_door[i].dir == DOOR_UPDOWN)
			{
				if (_door[i].frameY == 2 && _door[i].frameX == 5)
				{
					_door[i].state = DOOR_CLOSE;
					_door[i].frameY = 3, _door[i].frameX = 0;
				}
			}
		}
	}
}
	