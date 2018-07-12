#pragma once
#include "Enemy.h"
#include "progressBar.h"

enum BATDIRECTION
{
	BAT_RIGHT_MOVE,
	BAT_LEFT_MOVE,
	BAT_RIGHT_UP_MOVE,
	BAT_LEFT_UP_MOVE,
	BAT_RIGHT_DOWN_MOVE,
	BAT_LEFT_DOWN_MOVE,
	BAT_UP_MOVE,
	BAT_DOWN_MOVE,
	BAT_RIGHT_DIE,
	BAT_LEFT_DIE
};

//공격안하고 날아다니기만하는 박쥐
class Bat : public Enemy
{	
private:
	float _currentHP, _maxHP;

	BATDIRECTION _batDirection;
	animation* _batMotion;
	RECT rcCollision;	// 타일 검출 렉트

	int		randNum;	// 랜덤이동
	int		_detectionX, _detectionY;
	int		_moveCount;
	float _startX, _startY;//박쥐 이동 기준점
	bool _diedie;
	int _dieCount;
	//임시
	int j = 0;

public:
	Bat();
	~Bat();

	HRESULT init(float x, float y);
	void release();
	void update();
	void render();
	
	void move();//움직임 함수
	void changeAnimation(BATDIRECTION direction); //애니메이션 전환 함수
	//void changeDirection(); //방향전환 함수
	void rightMove();
	void leftMove();

	void tileDetection();	// 타일 검출

	void playerCollision();
	void die();
	void hitDamage();

	static void batDieMotion(void * obj);

	RECT  getBatRect() { return _rc; } //rc
};

