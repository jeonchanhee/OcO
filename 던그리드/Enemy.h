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

	float _jumpPower;
	float _gravity;


public:

	Enemy();
	~Enemy();

	HRESULT init();
	HRESULT init(const char* imageName, POINT position, float angle, float speed);
	void release();
	void update();
	void render();

	void changeFrmae();//프레임변화 함수
	void move();//움직이는 함수
	bool bulletCountFire(); //총알 발사 함수
	inline RECT getRect() { return _rc; } //렉트 반환 함수

	void setAngle(float angle); //각도 바꾸는 함수
	float getAngle();			//각도 받는 함수
	void setPoint(float x, float y);	//좌표 바꾸는 함수
};

