#pragma once
#include "singletonBase.h"
#include "image.h"


// ��ü �� ������ �Դϴ�   ���� �ο�Ź �帳�ϴ�
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

