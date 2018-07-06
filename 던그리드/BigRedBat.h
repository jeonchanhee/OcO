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
	BIGREDBATDIRECTION _bigRedBatDirection;
	animation* _bigRedBatMotion;

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

};

