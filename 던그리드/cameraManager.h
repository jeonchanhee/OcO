#pragma once
#include "singletonBase.h"
//#include "image.h"
//#include "tileNode.h"



class cameraManager  : public  singletonBase<cameraManager>
{
private:
	image*	_camera;
	POINT	_center;
	
	//image * _cameraDC;
	//image * _cameraDC2;
	//RECT _cameraRc;
	//RECT _cameraRc2;
	//float _cameraX, _cameraY;
	//float _cameraX2, _cameraY2;

public:
	HRESULT init();
	void update();
	void release();
	void render();
	void render(image* img);

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
	//image * getCameraDC() { return _cameraDC; }
	//image * getCameraDC2() { return _cameraDC2; }
	//RECT getCameraRc() { return _cameraRc; }
	//RECT getCameraRc2() { return _cameraRc2; }
	cameraManager();
	~cameraManager();

	HDC getCameraDC(void) { return _camera->getMemDC(); }
	void setCameraCenter(POINT point);
	POINT getCameraCenter(void) { return _center; }
	image* getCamera(void) { return _camera; }
};

