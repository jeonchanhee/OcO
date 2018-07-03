#pragma once
#include "Enemy.h"

enum BIGBATDIRECTION
{
	RIGHT_MOVE,
	LEFT_MOVE,
	RIGHT_ATTACK,
	LEFT_ATTACK,
	RIGHT_DIE,
	LEFT_DIE
};

class BigBat : public Enemy
{
	BIGBATDIRECTION _bigBatDirection;
	animation* _bigBatMotion;

public:
	BigBat();
	~BigBat();

	HRESULT init();
	void release();
	void update();
	void render();

	void move();
	void changeAnimation(BIGBATDIRECTION direction);

};

