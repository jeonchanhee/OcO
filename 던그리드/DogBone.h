#pragma once
#include "Enemy.h"

#define DOGBONESPEED 5.0f

enum DOGBONEDIRECTION
{
	DOGBONE_RIGHT_IDLE,
	DOGBONE_LEFT_IDLE,
	DOGBONE_RIGHT_MOVE,
	DOGBONE_LEFT_MOVE,
	DOGBONE_RIGHT_DIE,
	DOGBONE_LEFT_DIE,
	DOGBONE_RIGHT_JUMP,
	DOGBONE_LEFT_JUMP
};

class DogBone : public Enemy
{
private:
	DOGBONEDIRECTION _dogBoneDirection;
	animation* _dogBoneMotion;

	float _startY;

	RECT _rcCollision;
	string _str;
public:
	DogBone();
	~DogBone();

	HRESULT init(float x, float y);
	void release();
	void update();
	void render();

	void move(); //움직임 함수
	void rightMove(); //오른쪽 움직임
	void leftMove(); //왼쪽 움직임
	void rightJump(); //오른쪽 점프
	void leftJump(); //왼쪽 점프
	void changeDirection();//방향바꾸는 함수
	void changeAnimation(DOGBONEDIRECTION dogBoneDirection);//방향에 따라 애니메이션 바꾸는 함수
};

