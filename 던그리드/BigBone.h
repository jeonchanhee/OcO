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
	POINT		_renPoint[2]; //렌더할 x,y좌표 2개
	
	int		_index;

	RECT _rcCollision;

	RECT	_playerCollisionRc; //플레이어랑 충돌할 때 쓸 렉트(공격모션 때만 나오는 렉트임)
	bool _hit;
	int _hitCount;
	int _dieCount;
	bool _diedie;

public:
	BigBone();
	~BigBone();

	HRESULT init(float x, float y, int index);
	void release();
	void update();
	void render();

	void move(); //움직임 함수
	//void rightMove();//오른쪽 이동 함수
	//void leftMove(); //왼쪽 이동 함수
	static void rightAttack(void* obj);
	static void leftAttack(void* obj);
	static void dieMotion(void* obj);
	void changeDirection(); //방향전환 함수
	void changeAnimation(BIGBONEDIRECTION bigBoneDirection); //애니메이션 바꾸는 함수

	//콜백함수
	BIGBONEDIRECTION getBigBoneDirection() { return _bigBoneDirection; }
	void setBigBoneDirection(BIGBONEDIRECTION direction) { _bigBoneDirection = direction; }

	animation* getBigBoneMotion() { return _bigBoneMotion; }
	void setBigBoneMotion(animation* ani) { _bigBoneMotion = ani; }

	void playerColiision();
	void hitDamage();
};

