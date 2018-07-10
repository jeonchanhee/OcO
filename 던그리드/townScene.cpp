#include "stdafx.h"
#include "townScene.h"
#include "Player.h"


HRESULT townScene::init()
{
	SOUNDMANAGER->play("town");
	_player = SCENEMANAGER->getPlayerAddressLink();
	//픽쎌  =\=======

	_pixel = IMAGEMANAGER->addImage("pixelTown", 7680, 2400);
	HPEN pen, oldPen;
	pen = CreatePen(BS_SOLID, 20, RGB(0, 255, 0));
	oldPen = (HPEN)SelectObject(_pixel->getMemDC(), pen);

	LineMake(_pixel->getMemDC(), 1050, 1170, 1800, 1920);
	LineMake(_pixel->getMemDC(), 2220, 1920, 2980, 1170);
	LineMake(_pixel->getMemDC(), 4420, 1165, 5170, 1910);
	LineMake(_pixel->getMemDC(), 5580, 1925, 6336, 1175);

	SelectObject(_pixel->getMemDC(), oldPen);
	//제거  ===== 
	DeleteObject(oldPen);
	DeleteObject(pen);

	_isMapSet = true;
	_mapName = "map/townmap(80x25).map";
	_temp = 80;
	_tileX = 80, _tileY = 25;
	_dungeonNum = 11;
	mapload();
	return S_OK;
}

void townScene::release()
{

}

void townScene::update()
{
	_player->update();
}

void townScene::render()
{

	
	
		mapRender();
		IMAGEMANAGER->findImage("floor1")->render(DC, -23 * 96, 12 * 96);
		IMAGEMANAGER->findImage("floor2")->render(DC, 22 * 96, 12 * 96);
		IMAGEMANAGER->findImage("floor1")->render(DC, 57 * 96, 12 * 96);
		IMAGEMANAGER->findImage("floor0")->render(DC, 30 * 96, 17 * 96);
		IMAGEMANAGER->findImage("floor0")->render(DC, 36 * 96, 15 * 96);
	
	_player->render();

}

void townScene::mapload()
{
	HANDLE file;
	DWORD load;

	ZeroMemory(&_tiles, sizeof(tagTile) * TILEX * TILEY);

	file = CreateFile(_mapName.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &load, NULL);


	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].terrain == TOWN_GROUND) continue;
		if (_tiles[i].object == OBJ_DIAGONAL) continue;
		if (_tiles[i].terrainFrameX == 17 && _tiles[i].terrainFrameY == 1)  _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].terrainFrameX == 16 && _tiles[i].terrainFrameY == 1)  _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].terrainFrameX == 12 && _tiles[i].terrainFrameY == 25) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].terrainFrameX == 19 && _tiles[i].terrainFrameY == 18) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].terrainFrameX == 12 && _tiles[i].terrainFrameY == 25) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].terrainFrameX == 4 && _tiles[i].terrainFrameY == 0) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].terrainFrameX == 10 && _tiles[i].terrainFrameY == 1) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].terrainFrameX == 12 && _tiles[i].terrainFrameY == 0) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].terrainFrameX == 15 && _tiles[i].terrainFrameY == 18) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].terrainFrameX == 19 && _tiles[i].terrainFrameY == 1) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].terrainFrameX == 15 && _tiles[i].terrainFrameY == 1) _tiles[i].terrain = TOWN_GROUND;
		//대각
		if (_tiles[i].objFrameX == 7 && _tiles[i].objFrameY == 17) _tiles[i].object = OBJ_DIAGONAL;
		if (_tiles[i].objFrameX == 11 && _tiles[i].objFrameY == 0) _tiles[i].object = OBJ_DIAGONAL;
	}
	CloseHandle(file);

	CAMERAMANAGER->setCameraCenter(PointMake(0, 0));
}

void townScene::mapRender()
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
}
townScene::townScene()
{
}


townScene::~townScene()
{
}
