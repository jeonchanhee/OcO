#pragma once
#include "singletonBase.h"
#include "image.h"


// 전체 맵 사이즈 입니다   수정 부우탁 드립니다
#define BACKGROUNDSIZEX 8000
#define BACKGROUNDSIZEY 3000

#define CAMERA2X 1100
#define CAMERA2Y 1080


class cameraManager  : public  singletonBase<cameraManager>
{
private:
	
	image * _cameraDC;
	image * _cameraDC2;
	RECT _cameraRc;
	RECT _cameraRc2;
	float _cameraX, _cameraY;
	float _cameraX2, _cameraY2;

public:
	HRESULT init();
	void update();
	void release();
	  

	void setCameraX(float x) { _cameraX = x; }
	void setCameraX2(float x) { _cameraX2 = x; }
	void setCameraY(float y) { _cameraY = y; }
	void setCameraY2(float y) { _cameraY2 = y; }
	float getCameraX() { return _cameraX; }
	float getCameraX2() { return _cameraX2; }
	float getCameraY() { return _cameraY; }
	float getCameraY2() { return _cameraY2; }


	image * getCameraDC() { return _cameraDC; }
	image * getCameraDC2() { return _cameraDC2; }
	RECT getCameraRc() { return _cameraRc; }
	RECT getCameraRc2() { return _cameraRc2; }
	cameraManager();
	~cameraManager();
};

