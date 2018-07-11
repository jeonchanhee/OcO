#include "stdafx.h"
#include "townScene.h"
#include "Player.h"


HRESULT townScene::init()
{
	SOUNDMANAGER->play("town");
	_player = SCENEMANAGER->getPlayerAddressLink();
	//�Ƚ�  =\=======

	_pixel = IMAGEMANAGER->addImage("pixelTown", 7680, 2400);
	HPEN pen, oldPen;
	pen = CreatePen(BS_SOLID, 20, RGB(0, 255, 0));
	oldPen = (HPEN)SelectObject(_pixel->getMemDC(), pen);

	LineMake(_pixel->getMemDC(), 1050, 1170, 1800, 1920);
	LineMake(_pixel->getMemDC(), 2220, 1920, 2980, 1170);
	LineMake(_pixel->getMemDC(), 4420, 1165, 5170, 1910);
	LineMake(_pixel->getMemDC(), 5580, 1925, 6336, 1175);

	SelectObject(_pixel->getMemDC(), oldPen);
	//����  ===== 
	DeleteObject(oldPen);
	DeleteObject(pen);

	_trainer = IMAGEMANAGER->findImage("NƮ���̳�");
	_shop = IMAGEMANAGER->findImage("N������");
	_suckImg = IMAGEMANAGER->findImage("suck");
	int trainer[] = { 0,1,2,3,4,5 };
	int shop[] = { 15,16,17,18,19,20 };
	int suck[] = { 0,1,2,3,4,5,6,7,8,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51 };
	KEYANIMANAGER->addArrayFrameAnimation("trainer", "NƮ���̳�", trainer, 6, 5, true);
	KEYANIMANAGER->addArrayFrameAnimation("shop", "N������", shop, 6, 5, true);
	KEYANIMANAGER->addArrayFrameAnimation("suck", "suck", suck, 35, 20, false, moveDungeon,this);
	_training = KEYANIMANAGER->findAnimation("trainer");
	_shopping = KEYANIMANAGER->findAnimation("shop");
	_suck = KEYANIMANAGER->findAnimation("suck");
	_training->start();
	_shopping->start();
	_suck->start();
	
	_canMove = true;
	_sucking = false;
	_mapName = "map/townmap(80x25).map";
	_temp = 80;
	_tileX = 80, _tileY = 25;
	_dungeonNum = 11;
	mapload();
	setMinimap();
	return S_OK;
}

void townScene::release()
{

}

void townScene::update()
{
	//if(_canMove==true)
	_player->update();
}

void townScene::render()
{
	//if(KEYMANAGER->isToggleKey(VK_F3))
	
	
	IMAGEMANAGER->findImage("BackSky")->render(DC,CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2);
	IMAGEMANAGER->findImage("BackMountain")->render(DC, CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, (CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2)/12,0,WINSIZEX,WINSIZEY);
	IMAGEMANAGER->findImage("BackForest")->render(DC, CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, WINSIZEY*5/6+50, (CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2)/3.5,0,WINSIZEX,WINSIZEY);
	//IMAGEMANAGER->findImage("BackSky")->render(DC,0,0);
	mapRender();
	IMAGEMANAGER->findImage("floor1")->render(DC, -23 * 96, 12 * 96);
	IMAGEMANAGER->findImage("floor2")->render(DC, 22 * 96, 12 * 96);
	IMAGEMANAGER->findImage("floor1")->render(DC, 57 * 96, 12 * 96);
	IMAGEMANAGER->findImage("floor0")->render(DC, 30 * 96, 17 * 96);
	IMAGEMANAGER->findImage("floor0")->render(DC, 36 * 96, 15 * 96);
	IMAGEMANAGER->findImage("school")->render(DC, 1 * 96, 16* 96+24);
	IMAGEMANAGER->findImage("shop")->render(DC, 67 * 96-50, 4* 96-24);
	_trainer->aniRender(DC, 10 * 96, 20 * 96, _training);
	_shop->aniRender(DC, 72 * 96-20, 11* 96+10, _shopping);

	_player->render();
	//setMinimap();
	_minimap->render();
	dungeonGo();
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
		if (_tiles[i].objFrameX == 17 && _tiles[i].objFrameY == 1)  _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].objFrameX == 16 && _tiles[i].objFrameY == 1)  _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].objFrameX == 12 && _tiles[i].objFrameY == 25) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].objFrameX == 19 && _tiles[i].objFrameY == 18) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].objFrameX == 12 && _tiles[i].objFrameY == 25) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].objFrameX == 4  && _tiles[i].objFrameY == 0) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].objFrameX == 10 && _tiles[i].objFrameY == 1) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].objFrameX == 15 && _tiles[i].objFrameY == 18) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].objFrameX == 19 && _tiles[i].objFrameY == 1) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].objFrameX == 15 && _tiles[i].objFrameY == 1) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].objFrameX == 10 && _tiles[i].objFrameY == 25) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].objFrameX == 11 && _tiles[i].objFrameY == 25) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].objFrameX == 12 && _tiles[i].objFrameY == 0) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].objFrameX == 18 && _tiles[i].objFrameY == 1) _tiles[i].terrain = TOWN_GROUND;
		//�밢
		if (_tiles[i].objFrameX == 7 && _tiles[i].objFrameY == 17) _tiles[i].object = OBJ_DIAGONAL;
		if (_tiles[i].objFrameX == 11 && _tiles[i].objFrameY == 0) _tiles[i].object = OBJ_DIAGONAL;
	}
	CloseHandle(file);

	CAMERAMANAGER->setCameraCenter(PointMake(0, 0));
}

void townScene::setMinimap()
{
	_minimap = new minimap;
	_minimap->init();

	image* tempImg;
	tempImg = IMAGEMANAGER->addImage("��Ǫ", _tileX*TILESIZE, _tileY * TILESIZE);
	PatBlt(tempImg->getMemDC(), 0, 0, _tileX * TILESIZE, _tileY * TILESIZE, BLACKNESS);

	for (int i = 0; i < _tileY; i++)
	{
		for (int j = 0; j < _tileX; j++)
		{
			if (_tiles[i * _temp + j].object == OBJ_NONE) continue;
			//IMAGEMANAGER->frameRender("map", tempImg->getMemDC(), _tiles[i*_temp + j].rc.left, _tiles[i*_temp + j].rc.top, _tiles[i * _temp + j].terrainFrameX, _tiles[i * _temp + j].terrainFrameY);
			IMAGEMANAGER->frameRender("map", tempImg->getMemDC(), _tiles[i * _temp + j].rc.left, _tiles[i * _temp + j].rc.top, _tiles[i * _temp + j].objFrameX, _tiles[i * _temp + j].objFrameY);
		}
	}
	//tempImg->render(DC, 0, 0);
	_minimap->setMinimap(tempImg->getMemDC());
	//StretchBlt(DC, 0, 0, 500, 500, tempImg->getMemDC(), 0, 0, _tileX*TILESIZE, _tileY *TILESIZE, SRCCOPY);
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
		Rectangle(DC,_player->getRc().left, _player->getRc().top, _player->getRc().right, _player->getRc().bottom);
	}
}

void townScene::dungeonGo()
{
	RECT temp;
	RECT rc = RectMake( 2750, 2015, 2000, 30);
	if (_sucking == false)
	{
		if (IntersectRect(&temp, &_player->getRc(), &rc))
		{
			//_suckImg->render(DC, _player->getRc().left, rc.top - 100);
			_suck->start();
			_sucking = true;
			_canMove = false;
			if (_player->getIsLeftAttack() == true)
				_player->leftStop();
			else
				_player->rightStop();
		}
	}
	else
		_suckImg->aniRender(DC, _player->getRc().left-350,1510,_suck);
	//Rectangle(DC, rc.left, rc.top, rc.right, rc.bottom);
}

 void townScene::moveDungeon(void* object)
{
	 townScene* T = (townScene*)object;
	 T->_sucking = false;
	 _canMove = true;
	 SCENEMANAGER->changeScene("������1");
}

townScene::townScene()
{
}


townScene::~townScene()
{
}
