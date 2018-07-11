#pragma once
#include "Enemy.h"
#include "MapTool.h"

#define BIGBONESPEED 5.0f;

enum BIGBONEDIRECTION
{
	BIGBONE_RIGHT_IDLE,
	BIGBONE_LEFT_IDLE,
	BIGBONE_RIGHT_MOVE,
	BIGBONE_LEFT_MOVE,
	BIGBONE_DIE,
	BIGBONE_RIGHT_ATTACK,
	BIGBONE_LEFT_ATTACK
};

class BigBone : public Enemy
{
private:
	MapTool* _mapTool;
	BIGBONEDIRECTION _bigBoneDirection;
	animation* _bigBoneMotion;
	POINT		_renPoint[2]; //������ x,y��ǥ 2��

	int		_index;

	RECT _rcCollision;
public:
	BigBone();
	~BigBone();

	HRESULT init(float x, float y, int index);
	void release();
	void update();
	void render();

	void move(); //������ �Լ�
	//void rightMove();//������ �̵� �Լ�
	//void leftMove(); //���� �̵� �Լ�
	static void rightAttack(void* obj);
	static void leftAttack(void* obj);
	void changeDirection(); //������ȯ �Լ�
	void changeAnimation(BIGBONEDIRECTION bigBoneDirection); //�ִϸ��̼� �ٲٴ� �Լ�

	//�ݹ��Լ�
	BIGBONEDIRECTION getBigBoneDirection() { return _bigBoneDirection; }
	void setBigBoneDirection(BIGBONEDIRECTION direction) { _bigBoneDirection = direction; }

	animation* getBigBoneMotion() { return _bigBoneMotion; }
	void setBigBoneMotion(animation* ani) { _bigBoneMotion = ani; }

	void playerColiision();
	void hitDamage(float damage);
};

