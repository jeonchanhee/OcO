#pragma once
#include "singletonBase.h"
#include "image.h"


// 전체 맵 사이즈 입니다   수정 부우탁 드립니다
#define BACKGROUNDSIZEX 3000
#define BACKGROUNDSIZEY 3000

class cameraManager  : public  singletonBase<cameraManager>
{
private:
	
	image * _cameraDC;
	RECT _cameraRc;
	float _cameraX, _cameraY;

public:
	HRESULT init();
	void update();
	void release();
	  

	void setCameraX(float x) { _cameraX = x; }
	void setCameraY(float y) { _cameraY = y; }
	float getCameraX() { return _cameraX; }
	float getCameraY() { return _cameraY; }


	image * getCameraDC() { return _cameraDC; }
	RECT getCameraRc() { return _cameraRc; }
	cameraManager();
	~cameraManager();
};

