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

	void move(); //������ �Լ�
	void rightMove(); //������ ������
	void leftMove(); //���� ������
	void rightJump(); //������ ����
	void leftJump(); //���� ����
	void changeDirection();//����ٲٴ� �Լ�
	void changeAnimation(DOGBONEDIRECTION dogBoneDirection);//���⿡ ���� �ִϸ��̼� �ٲٴ� �Լ�
};

