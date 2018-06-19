#pragma once
#include "gameNode.h"

class ship : public gameNode
{
protected:
	image* _image;		//우주선 이미지
	RECT _rc;			//렉트
	float _x, _y;		//중점좌표
	float _angle;		//각도
	float _speed;		//속도
	float _radius;		//반지름

public:
	ship();
	~ship();

	virtual HRESULT init(const char* imageName, int x, int y);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void draw();
	virtual void keyControl();
	virtual void move();

};

