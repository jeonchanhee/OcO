#pragma once
#include "gameNode.h"

//적 클래스 
class enemy : public gameNode
{
protected:
	//상속으로 찍어내기위한 프로텍티드(상속관계에서만 접근할수있다)
	image*	_imageName;			//적 이미지
	RECT	_rc;				//적 렉트

	int		_currentFrameX;		//각각의 이미지 관리를 위한 프레임번호
	int		_currentFrameY;

	int		_count;				//프레임	카운트
	int		_fireCount;			//발사	카운트
	int		_rndFireCount;		//랜덤하게 발사할 카운트

public:
	enemy();
	~enemy();

	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update();
	void render();

	void move();		//움직임 함수
	void draw();		//그려주는 함수

	bool bulletCountFire();		//총알 발사 함수

	inline RECT getRect() { return _rc; }
	
};

