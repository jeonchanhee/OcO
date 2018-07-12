#include "stdafx.h"
#include "minimap.h"
#include "Enemy.h"

minimap::minimap()
{
}


minimap::~minimap()
{
}

HRESULT minimap::init(bool isDungeon)
{
	_isDungeon = isDungeon;
	if (_isDungeon)
		_mapX = 300, _mapY = 150;
	else
		_mapX = 400, _mapY = 200;

	if(!_isDungeon)
		_minimap = IMAGEMANAGER->addImage("마을", _mapX, _mapY);
	else
		_minimap = IMAGEMANAGER->addImage("던전", _mapX, _mapY);

	_playerIcon.img = IMAGEMANAGER->findImage("playerIcon");

	for (int i = 0; i < 2; i++)
	{
		_npcIcon[i].img = new image;
		_npcIcon[i].img->init("image/icon/npcIcon(20x20).bmp", 20, 20, true, RGB(255, 0, 255));
		_npcIcon[i].x = _npcIcon[i].y = 0;
	}

	_portalIcon.img = IMAGEMANAGER->findImage("portalIcon");
	_portalIcon.x = _portalIcon.y = 0;

	return S_OK;
}

void minimap::release()
{
}

void minimap::render()
{
	//_minimap->render(DC, CAMERAMANAGER->getCameraCenter().x + WINSIZEX / 2 - 450, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2 + 50);
	if (!_isDungeon)
	{
		RectangleMake(UIDC, WINSIZEX - _mapX - 60, 40, _mapX + 20, _mapY + 20);
		_minimap->render(UIDC, WINSIZEX - _mapX - 50, 50);
	}
	else
	{
		RectangleMake(UIDC, WINSIZEX - _mapX - 60, 40, _mapX + 20, _mapY + 20);
		_minimap->render(UIDC, WINSIZEX - _mapX - 50, 50);
	}
	
	for (int i = 0; i < _vDoorIcon.size(); i++)
	{
		if(_dungeonNum == 4)
			_vDoorIcon[i].img->render(UIDC, WINSIZEX - _mapX - 50 + _vDoorIcon[i].x, 50 + _vDoorIcon[i].y);
		else
		_vDoorIcon[i].img->render(UIDC, WINSIZEX - _mapX - 50 + _vDoorIcon[i].x, 50 + _vDoorIcon[i].y);
	}

	if (_portalIcon.x != 0)
	{
		if(_dungeonNum == 5)
			_portalIcon.img->frameRender(UIDC, WINSIZEX - _mapX - 50 + _portalIcon.x, 30 + _portalIcon.y, 0, 0);
		else
		_portalIcon.img->frameRender(UIDC, WINSIZEX - _mapX - 50 + _portalIcon.x, 50 + _portalIcon.y, 0, 0);
	}

	for (int i = 0; i < 2; i++)
	{
		if (_npcIcon[i].x != 0)
			_npcIcon[i].img->render(UIDC, WINSIZEX - _mapX - 50 + _npcIcon[i].x, 50 + _npcIcon[i].y);
			//_npcIcon[i].img->render(UIDC, WINSIZEX - _mapX, 50);
	}
	
	for (int i = 0; i < _vEnemyIcon.size(); i++)
	{
		if (!_vEnemyIcon[i].die)
		{
			if (_dungeonNum == 5)
				_vEnemyIcon[i].img->render(UIDC, WINSIZEX - _mapX - 50 + _vEnemyIcon[i].x, 40 + _vEnemyIcon[i].y);
			else
				_vEnemyIcon[i].img->render(UIDC, WINSIZEX - _mapX - 50 + _vEnemyIcon[i].x, 50 + _vEnemyIcon[i].y);
		}
	}
	
	_playerIcon.img->render(UIDC, WINSIZEX - _mapX - 50 + _playerIcon.x, 50 + _playerIcon.y);
}

void minimap::update()
{
}

void minimap::setMinimap(HDC dc)
{
	PatBlt(_minimap->getMemDC(), 0, 0, _mapX, _mapY, BLACKNESS);
	StretchBlt(_minimap->getMemDC(), 0, 0, _mapX, _mapY, dc, 0, 0, _tileX*TILESIZE, _tileY *TILESIZE, SRCCOPY);
}

void minimap::setPlayerXY(float x, float y)
{
	_playerIcon.x = x;
	_playerIcon.y = y;
}

void minimap::setNPCXY(int idx, float x, float y)
{
	_npcIcon[idx].x = x, _npcIcon[idx].y = y;
}

void minimap::setPortalXY(float x, float y)
{
	_portalIcon.x = x, _portalIcon.y = y;
}

void minimap::setEnemyXY(float x, float y)
{
	tagIcon icon;
	icon.img = IMAGEMANAGER->findImage("enemyIcon");
	icon.x = x;
	icon.y = y;
	icon.die = false;
	_vEnemyIcon.push_back(icon);
}

void minimap::changeEnemyXY(int idx, float x, float y)
{
	_vEnemyIcon[idx].x = x;
	_vEnemyIcon[idx].y = y;
}

void minimap::setDieMonster(int idx)
{
	_vEnemyIcon[idx].die = true;
}

void minimap::setDoorXY(float x, float y, bool height)
{
	tagIcon icon;
	icon.img = new image;
	if (height)
	{
		if(_dungeonNum != 4)
			icon.img->init("image/icon/heightDoorIcon(10x50).bmp", 10, 50, true, RGB(255, 0, 255));
		else
			icon.img->init("image/icon/heightDoorIcon(10x50).bmp", 10, 30, true, RGB(255, 0, 255));
	}
	else
	{
		if(_dungeonNum != 4)
			icon.img->init("image/icon/widthDoorIcon(50x10).bmp", 50, 10, true, RGB(255, 0, 255));
		else
			icon.img->init("image/icon/widthDoorIcon(50x10).bmp", 40, 10, true, RGB(255, 0, 255));
	}
	icon.x = x;
	icon.y = y;
	_vDoorIcon.push_back(icon);
}
