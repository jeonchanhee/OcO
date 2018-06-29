#include "stdafx.h"
#include "cameraManager.h"


HRESULT cameraManager::init()
{
	_cameraDC = IMAGEMANAGER->addImage("Ä«¸Þ¶óDC", BACKGROUNDSIZEX, BACKGROUNDSIZEY);
	_cameraX = 0; _cameraY = 0;
	return S_OK;
}

void cameraManager::update()
{
	_cameraRc = RectMake(_cameraX, _cameraY, WINSIZEX, WINSIZEY);
}


void cameraManager::release()
{
}

cameraManager::cameraManager(){}
cameraManager::~cameraManager(){}
