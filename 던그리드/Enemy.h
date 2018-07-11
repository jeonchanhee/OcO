#pragma once
#include "gameNode.h"
#include "progressBar.h"

class Player; //플레이어 클래스 전방선언

class Enemy :	public gameNode
{
protected:
	Player* _player;
	image* _img;				//적 이미지
	RECT _rc;				//적 렉트
	int _frameX, _frameY;	//프레임 번호

	float _x, _y;			//적 x, y좌표
	float _speed, _angle;	//스피드와 각도

	int _count;				//프레임 카운트
	int _fireCount;			//발사 카운트
	int _rndFireCount;		//랜덤하게 발사할 카운트

	float _jumpPower;		//점프파워
	float _gravity;			//중력
	bool _isJumping;		//점프중이냐 아니냐

	progressBar* _progressBar; //체력바
	float _currentHP, _maxHP; //현재체력과 최대체력
	
public:

	Enemy();
	~Enemy();

	HRESULT init(const char* imageName, float x, float y, float angle, float speed);
	void release();
	void update();
	void render();

	void changeFrame();//프레임변화 함수
	void move();//움직이는 함수
	bool bulletCountFire(); //총알 발사 함수
	inline RECT getRect() { return _rc; } //렉트 반환 함수

	void setAngle(float angle); //각도 바꾸는 함수
	//float getAngle();			//각도 받는 함수
	void setPoint(float x, float y);	//좌표 바꾸는 함수

	float getX() { return _x; }
	float getY() { return _y; }

	int getcount() { return _count; }

	int getCurrentHp() { return _currentHP; } //현재 hp
	int getMaxHp() { return _maxHP; } //전체hp
	void setCurrentHp(int currentHP) { _currentHP = currentHP; }
	void setMaxHp(int maxHP) { _maxHP = maxHP; }
	RECT  getEnemyRect() { return _rc; } //arrow,boss는 클래스 안에 따로 있음

	void setPlayerAddressLink(Player* player) { _player = player; }
	
};

