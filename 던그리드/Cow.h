#pragma once
#include "Enemy.h"

#define COWSPEED 9.0f;

enum COWDIRECTION
{
	COW_RIGHT_MOVE,
	COW_LEFT_MOVE,
	COW_RIGHT_CHARGE,
	COW_LEFT_CHARGE,
	COW_RIGHT_ATTACK,
	COW_LEFT_ATTACK,
	COW_DIE
};

class Cow : public Enemy
{
	COWDIRECTION _cowDirection;
	animation* _cowMotion;

	RECT _rcCollision;
	bool _hit;

public:
	Cow();
	~Cow();

	HRESULT init(float x , float y);
	void release();
	void update();
	void render();

	void move();
	void changeDirection();

	static void rightCharge(void* obj);
	static void leftCharge(void* obj);

	static void rightAttack(void* obj);
	static void leftAttack(void* obj);
	
	void changeAnimation(COWDIRECTION cowDirection);

	//콜백함수
	COWDIRECTION getCowDirection() { return _cowDirection; }
	void setCowDirection(COWDIRECTION cowDirection) { _cowDirection = cowDirection; }

	animation* getCowMotion() { return _cowMotion; }
	void setCowMotion(animation* ani) { _cowMotion = ani; }

	void playerCollision();
	void hitDamage(float damage);

};

