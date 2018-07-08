#include "stdafx.h"
#include "mapSelectScene.h"


mapSelectScene::mapSelectScene()
{
}


mapSelectScene::~mapSelectScene()
{
}

HRESULT mapSelectScene::init()
{
	_isMapSet = true;
	_mapIdx = 0;
	_isMapSet = true;
	chooseMap(_mapIdx);
	return S_OK;
}

void mapSelectScene::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_F1))
			chooseMap(1);
		if (KEYMANAGER->isOnceKeyDown(VK_F2))
			chooseMap(2);
		if (KEYMANAGER->isOnceKeyDown(VK_F3))
			chooseMap(3);
		if (KEYMANAGER->isOnceKeyDown(VK_F4))
			chooseMap(4);
		if (KEYMANAGER->isOnceKeyDown(VK_F5))
			chooseMap(5);
		if (KEYMANAGER->isOnceKeyDown(VK_F6))
			chooseMap(6);
		if (KEYMANAGER->isOnceKeyDown(VK_F7))
			chooseMap(7);
		if (KEYMANAGER->isOnceKeyDown(VK_F8))
			chooseMap(8);
		if (KEYMANAGER->isOnceKeyDown(VK_F9))
			chooseMap(9);
		if (KEYMANAGER->isOnceKeyDown(VK_F10))
			chooseMap(10);
		if (KEYMANAGER->isOnceKeyDown(VK_F11))
			chooseMap(11);
		if (KEYMANAGER->isOnceKeyDown(VK_F12))
			chooseMap(0);
	}
}

void mapSelectScene::release()
{
}

void mapSelectScene::render()
{
	printMap(_mapIdx);
}

void mapSelectScene::load()
{
	HANDLE   file;
	DWORD   load;
	ZeroMemory(&_tiles, sizeof(tagTile) * TILEX * TILEY);

	file = CreateFile(_mapName.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &load, NULL);

	CloseHandle(file);
}


void mapSelectScene::printMap(int idx)
{
	int temp = 0;

	if (idx == 0)
		temp = 80;
	if (idx == 1)
		temp = 29;
	if (idx == 2)
		temp = 29;
	if (idx == 3)
		temp = 100;
	if (idx == 4)
		temp = 30;
	if (idx == 5)
		temp = 25;
	if (idx == 6) //이상...
		temp = 50;
	if (idx == 7)
		temp = 25;
	if (idx == 8)
		temp = 20;
	if (idx == 9)
		temp = 50;
	if (idx == 10)
		temp = 50;
	if (idx == 11)
		temp = 25;

	//지형
	for (int i = (CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2) / 96; i < (CAMERAMANAGER->getCameraCenter().y + WINSIZEY / 2) / 96 + 1; ++i)
	{
		for (int j = (CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2) / 96; j < (CAMERAMANAGER->getCameraCenter().x + WINSIZEX / 2) / 96 + 1; ++j)
		{
			//if (i >= _tileX || j >= _tileY) continue;

			IMAGEMANAGER->frameRender("map", DC, _tiles[i * temp + j].rc.left, _tiles[i * temp + j].rc.top, _tiles[i * temp + j].terrainFrameX, _tiles[i * temp + j].terrainFrameY);

			char str[128];
			sprintf_s(str, "%d", i * temp + j);
			TextOut(DC, _tiles[i * temp + j].rc.left, _tiles[i * temp + j].rc.top, str, strlen(str));
		}
	}

	//for (int i = 0; i < TILEX * TILEY; i++)
	//{
	//   //if (i % 50 > _tileX || i > TILEX*2 * _tileY + _tileX) continue;
	//   IMAGEMANAGER->frameRender("map", DC, _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	//}

	

	//if (KEYMANAGER->isToggleKey(VK_SPACE)) return;
	//
	//for (int i = 0; i < 28; ++i)
	//{
	//   for (int j = 0; j < 49; ++j)
	//   {
	//      RectangleMake(DC, 96 * j, 96 * i, 96, 96);
	//   }
	//}

	// 오브젝트
	//if (KEYMANAGER->isToggleKey('N'))
	{
		for (int i = (CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2) / 96; i < (CAMERAMANAGER->getCameraCenter().y + WINSIZEY / 2) / 96 + 1; ++i)
		{
			for (int j = (CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2) / 96; j < (CAMERAMANAGER->getCameraCenter().x + WINSIZEX / 2) / 96 + 1; ++j)
			{
				if (_tiles[i * temp + j].object == OBJ_NONE) continue;

				IMAGEMANAGER->frameRender("map", DC, _tiles[i * temp + j].rc.left, _tiles[i * temp + j].rc.top, _tiles[i * temp + j].objFrameX, _tiles[i * temp + j].objFrameY);
			}
		}

		//for (int i = 0; i < TILEX * TILEY; i++)
		//{
		//   //if (i % 50 > _tileX || i > TILEX*2 * _tileY + _tileX) continue;
		//   // 오브젝트 속성이 아니면 그리지마
		//   if (_tiles[i].object == OBJ_NONE) continue;
		//
		//   IMAGEMANAGER->frameRender("map", DC, _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
		//}
	}


	//if (KEYMANAGER->isToggleKey(VK_TAB))
	//{
	//   for (int i = 0; i < TILEX * TILEY; i++)
	//   {
	//      //if (i % 50 > TILEVALUE[0][0] || i > TILEX * 2 * TILEVALUE[0][1] + TILEVALUE[0][0]) continue;
	//      //IMAGEMANAGER->frameRender("map", DC, _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	//      Rectangle(DC, _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom);
	//      char str[128];
	//      sprintf_s(str, "%d", i);
	//      TextOut(DC, _tiles[i].rc.left, _tiles[i].rc.top, str, strlen(str));
	//      //count++;
	//   }
	//}
}

void mapSelectScene::chooseMap(int idx)
{
	_mapIdx = idx;

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

	load();
	setCamera();
}

void mapSelectScene::setCamera(void)
{
	CAMERAMANAGER->setCameraCenter(PointMake(0, 0));
}