#pragma once
#include "singletonBase.h"
//#include "image.h"
//#include "tileNode.h"
#define moveValue 1



class cameraManager  : public  singletonBase<cameraManager>
{
private:
	image*	_camera;
	POINT	_center;
	
	image * _cameraDC;
	POINT	_point;
	/*
	image * _cameraDC2;
	RECT _cameraRc;
	RECT _cameraRc2;
	float _cameraX, _cameraY;
	float _cameraX2, _cameraY2;*/

public:
	HRESULT init();
	void update();
	void release();

	void cameraShaking();

	//void cameraShaking();
	//
	//void setCameraX(float x) { _cameraX = x; }
	//void setCameraX2(float x) { _cameraX2 = x; }
	//void setCameraY(float y) { _cameraY = y; }
	//void setCameraY2(float y) { _cameraY2 = y; }
	//float getCameraX() { return _cameraX; }
	//float getCameraX2() { return _cameraX2; }
	//float getCameraY() { return _cameraY; }
	//float getCameraY2() { return _cameraY2; }
	//
	//
	//
	//image * getCameraDC() { return _cameraDC; }
	//image * getCameraDC2() { return _cameraDC2; }
	//RECT getCameraRc() { return _cameraRc; }
	//RECT getCameraRc2() { return _cameraRc2; }
	cameraManager();
	~cameraManager();

	void render(void);
	void render(image* img);

	HDC getCameraDC(void) { return _camera->getMemDC(); }
	HDC getCameraDC2(void) { return _cameraDC->getMemDC(); }
	void setCameraCenter(POINT point);

	// 지우지 말아주세요 setCameraCenter 쓰니까 대각선처리가 부드럽지 못하드라구요 
	void setCameraX(long x);
	void setCameraY(long y);
	//주석도 자제좀 

	POINT getCameraCenter(void) { return _center; }
	POINT getCameraPoint(void) { return _point; }
	image* getCamera(void) { return _camera; }

};

