#pragma once
#include "Enemy.h"
#include "progressBar.h"

enum BATDIRECTION
{
	BAT_RIGHT_MOVE,
	BAT_LEFT_MOVE,
	BAT_RIGHT_DIE,
	BAT_LEFT_DIE
};

//공격안하고 날아다니기만하는 박쥐
class Bat : public Enemy
{
private:
	progressBar* _progressBar;
	float _currentHP, _maxHP;

	BATDIRECTION _batDirection;
	animation* _batMotion;
	RECT			_detectionrc;		// 타일 검출 렉트

	int		_detectionX, _detectionY;
	float _startX, _startY;//박쥐 이동 기준점

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

	void playerCollision();
	void hitDamage(float damage);

	void tileDetection();	// 타일 검출
};

