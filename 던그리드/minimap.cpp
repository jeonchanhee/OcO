#include "stdafx.h"
#include "minimap.h"


minimap::minimap()
{
}


minimap::~minimap()
{
}

HRESULT minimap::init()
{
	_minimap = IMAGEMANAGER->addImage("¹Ì´Ï¸Ê", 400, 200);
	return S_OK;
}

void minimap::release()
{
}

void minimap::render()
{
	_minimap->render(DC, CAMERAMANAGER->getCameraCenter().x + WINSIZEX / 2 - 450, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2 + 50);
}

void minimap::update()
{
}

void minimap::setMinimap(HDC dc)
{
	PatBlt(_minimap->getMemDC(), 0, 0, 400, 200, BLACKNESS);
	StretchBlt(_minimap->getMemDC(), 0, 0, 400, 200, dc, 0, 0, _tileX*TILESIZE, _tileY *TILESIZE, SRCCOPY);

	
}
