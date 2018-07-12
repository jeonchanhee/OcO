#include "stdafx.h"
#include "cameraManager.h"


HRESULT cameraManager::init()
{
	_camera = IMAGEMANAGER->addImage("CAMERA", WINSIZEX, WINSIZEY);
	_center = PointMake(WINSIZEX / 2, WINSIZEY / 2);
	

	_cameraDC = IMAGEMANAGER->addImage("카메라DC", 600, 1080,true,RGB(0,0,0));
	_point = PointMake(0, 0);
	//_cameraDC2 = IMAGEMANAGER->addImage("카메라DC2", BACKGROUNDSIZEX, BACKGROUNDSIZEY);
	//_cameraX = 0; _cameraY = 0;
	//_cameraX2 = 0; _cameraY2 = 0;
	return S_OK;
	
} 

void cameraManager::update()
{
	//_cameraRc = RectMake(_cameraX, _cameraY, WINSIZEX, WINSIZEY);
	//_cameraRc2 = RectMake(_cameraX2, _cameraY2, CAMERA2X, CAMERA2Y);
}


void cameraManager::release()
{
}
// don't erase  plz

void cameraManager::cameraShaking()
{
	int rand = RND->getInt(4);
	switch (rand)
	{
	case 0:
		_center.x += moveValue;
		_center.y += moveValue;
		break;
	case 1:
		_center.x += moveValue;
		_center.y -= moveValue;
		break;
	case 2:
		_center.x -= moveValue;
		_center.y += moveValue;
		break;
	case 3:
		_center.x -= moveValue;
		_center.y -= moveValue;
		break;

	}
}


cameraManager::cameraManager(){}
cameraManager::~cameraManager(){}

void cameraManager::render(void)
{

}

void cameraManager::render(image* img)
{
	GdiTransparentBlt(img->getMemDC(), _center.x - WINSIZEX / 2, _center.y - WINSIZEY / 2, WINSIZEX, WINSIZEY,
		_camera->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, RGB(0, 0, 0));
}

void cameraManager::setCameraCenter(POINT point)
{
	_center.x = point.x;
	_center.y = point.y;

	//if (_isMapSet)
	{
	//	if (_center.x <= WINSIZEX / 2) _center.x = WINSIZEX / 2;
//		if (_center.x >= _tileX * 96 - WINSIZEX / 2) _center.x = _tileX * 96 - WINSIZEX / 2;
//		if (_center.y <= WINSIZEY / 2) _center.y = WINSIZEY / 2;
	//	if (_center.y >= _tileY * 96 - WINSIZEY / 2) _center.y = _tileY * 96 - WINSIZEY / 2;
	}
}

void cameraManager::setCameraPoint(POINT point)
{
	_point.x = point.x;
	_point.y = point.y;

	//if (_isMapSet)
	{
		if (_point.x <= WINSIZEX / 2) _point.x = WINSIZEX / 2;
		if (_point.x >= _tileX * 96 - WINSIZEX / 2) _point.x = _tileX * 96 - WINSIZEX / 2;
		if (_point.y <= WINSIZEY / 2) _point.y = WINSIZEY / 2;
		if (_point.y >= _tileY * 96 - WINSIZEY / 2) _point.y = _tileY * 96 - WINSIZEY / 2;
	}
}

//주석자제  쓰고있는 거에요 ~
void cameraManager::setCameraX(long x)
{
	_center.x = x;
//	if (_isMapSet)
	{
		if (_center.x <= WINSIZEX / 2) _center.x = WINSIZEX / 2;
		if (_center.x >= _tileX * 96 - WINSIZEX / 2) _center.x = _tileX * 96 - WINSIZEX / 2;
		if (_center.y <= WINSIZEY / 2) _center.y = WINSIZEY / 2;
		if (_center.y >= _tileY * 96 - WINSIZEY / 2) _center.y = _tileY * 96 - WINSIZEY / 2;
	}
}

void cameraManager::setCameraY(long y)
{
	_center.y = y;
	//if (_isMapSet)
	{
		if (_center.x <= WINSIZEX / 2) _center.x = WINSIZEX / 2;
		if (_center.x >= _tileX * 96 - WINSIZEX / 2) _center.x = _tileX * 96 - WINSIZEX / 2;
		if (_center.y <= WINSIZEY / 2) _center.y = WINSIZEY / 2;
		if (_center.y >= _tileY * 96 - WINSIZEY / 2) _center.y = _tileY * 96 - WINSIZEY / 2;
	}
}
