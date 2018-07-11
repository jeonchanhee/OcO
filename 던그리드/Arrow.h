#pragma once
#include "Enemy.h"
#include "progressBar.h"

#define ARROWSPEED 10.0f

struct tagArrow
{
	image* img; 
	RECT rc;
	float x, y;
};

class Player; //플레이어 클래스 전방선언

class Arrow : public Enemy
{
private:
	Player * _player;

	tagArrow _arrow[3]; //0활쟁이.1활.2화살
	bool _isShoot;
	POINT _bowCenter;//활 중앙

	int	_index;

	progressBar* _progressBar; //체력바
	float _currentHP, _maxHP; //현재체력과 최대체력


public:
	Arrow();
	~Arrow();

	HRESULT init(float x, float y);
	void release();
	void update();
	void render();

	void frameMove();
	void shootArrow();
	void fireArrow(); //활쟁이가 마우스방향으로 활쏘게 하는 내용

	void playerCollision(); //플레이어와 활쟁이의 충돌 함수
	void hitDamage(float damage);//hp깎이게 하는 함수

	int getCurrentHp() { return _currentHP; } //현재 hp
	int getMaxHp() { return _maxHP; } //전체hp
	void setCurrentHp(int currentHP) { _currentHP = currentHP; }
	void setMaxHp(int maxHP) { _maxHP = maxHP; }
	RECT  getArrowRect() { return _arrow[0].rc; } //rc

	void setPlayerAddressLink(Player* player) { _player = player; }
};