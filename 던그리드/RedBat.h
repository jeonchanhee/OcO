#pragma once
#include "Enemy.h"

enum REDBATDIRECTION
{
	RIGHT_MOVE,
	LEFT_MOVE,
	RIGHT_ATTACK,
	LEFT_ATTACK,
	RIGHT_DIE,
	LEFT_DIE
};

class RedBat : public Enemy
{
	REDBATDIRECTION _redBatDirection;
	animation* _redBatMotion;
	
	float _startX, _startY;

public:
	RedBat();
	~RedBat();

	HRESULT init();
	void release();
	void update();
	void render();

	void move();
	void rightMove();
	void leftMove();
	void changeAnimation(REDBATDIRECTION direction);

};

