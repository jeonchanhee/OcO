#include "stdafx.h"
#include "cameraManager.h"


HRESULT cameraManager::init()
{
	_cameraDC = IMAGEMANAGER->addImage("카메라DC", BACKGROUNDSIZEX, BACKGROUNDSIZEY);
	_cameraDC2 = IMAGEMANAGER->addImage("카메라DC2", BACKGROUNDSIZEX, BACKGROUNDSIZEY);
	_cameraX = 0; _cameraY = 0;
	_cameraX2 = 0; _cameraY2 = 0;
	return S_OK;
}

void cameraManager::update()
{
	_cameraRc = RectMake(_cameraX, _cameraY, WINSIZEX, WINSIZEY);
	_cameraRc2 = RectMake(_cameraX2, _cameraY2, CAMERA2X, CAMERA2Y);
}


void cameraManager::release()
{
}

cameraManager::cameraManager(){}
cameraManager::~cameraManager(){}
