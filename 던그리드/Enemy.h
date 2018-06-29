#pragma once
#include "gameNode.h"

class Enemy :	public gameNode
{
protected:
	image* _img;				//적 이미지
	RECT _rc;				//적 렉트
	int _frameX, _frameY;	//프레임 번호

	float _x, _y;			//적 x, y좌표
	float _speed, _angle;	//스피드와 각도

	int _count;				//프레임 카운트
	int _fireCount;			//발사 카운트
	int _rndFireCount;		//랜덤하게 발사할 카운트


public:

	HRESULT init();
	HRESULT init(const char* imageName, POINT position, float angle, float speed);
	void release();
	void update();
	void render();

	Enemy();
	~Enemy();
};

