#pragma once
#include "Enemy.h"

enum BIGREDBATDIRECTION
{
	BIGREDBAT_RIGHT_MOVE,
	BIGREDBAT_LEFT_MOVE,
	BIGREDBAT_RIGHT_ATTACK,
	BIGREDBAT_LEFT_ATTACK,
	BIGREDBAT_RIGHT_DIE,
	BIGREDBAT_LEFT_DIE
};

class BigRedBat : public Enemy
{
private:
	BIGREDBATDIRECTION _bigRedBatDirection;
	animation* _bigRedBatMotion;
	bool _isAttack;
	bool _diedie;

	int _diecount;
	int _index;
public:
	BigRedBat();
	~BigRedBat();

	HRESULT init(float x, float y);
	void release();
	void update();
	void render();

	void attackMove();

	static void rightAttack(void* obj);
	static void leftAttack(void* obj);

	void changeAnimation(BIGREDBATDIRECTION bigRedBatDirection);

	//콜백함수
	BIGREDBATDIRECTION getBigRedBatDirection() { return _bigRedBatDirection; }
	void setBigRedBatDirection(BIGREDBATDIRECTION dir) { _bigRedBatDirection = dir; }

	animation* getBigRedBatMotion() { return _bigRedBatMotion; }
	void setBigRedBatMotion(animation* ani) { _bigRedBatMotion = ani; }

	void playerCollision();
	void hitDamage();
	void die();
	static void bigRedBatDieMotion(void * obj);
	void hitDamage(float damage);

	bool getisAtteck2() { return _isAttack; }
	void setisAtteck2(bool isAttack) { _isAttack = isAttack; }

	bool getdiedie() { return _diedie;	}
};

