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
	//RectangleMake(DC, 100, 100, 100, 100);
	_minimap->render(UIDC, 100, 100);
	
}

void minimap::update()
{
}

void minimap::setMinimap(HDC dc)
{
	PatBlt(_minimap->getMemDC(), 0, 0, 400, 200, WHITENESS);
	StretchBlt(_minimap->getMemDC(), 0, 0, 400, 200, dc, 0,0,TILEVALUE[_dungeonNum][0]*TILESIZE, TILEVALUE[_dungeonNum][1] * TILESIZE, SRCCOPY);
}
