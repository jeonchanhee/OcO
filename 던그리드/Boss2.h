#pragma once
#include "Enemy.h"

#define BOSSSPEED 3.0f

enum BOSSHEADDIRECTION
{
	HEAD_IDLE,
	HEAD_ATTACK,
	HEAD_DIE
};

enum BOSSLEFTDIRECTION
{
	LEFT_IDLE,
	LEFT_MOVE,
	LEFT_LASER
};


struct tagBoss
{
	RECT rc;
	image* img;
	float x, y;
};

class Boss2 : public Enemy
{
private:
	tagBoss _boss[3];
	
	BOSSHEADDIRECTION _bossHeadDirection;
	BOSSLEFTDIRECTION _bossLeftDirection;

	animation* _bossMotion[3]; //0왼손.1머리.2오른손
	

public:
	Boss2();
	~Boss2();

	HRESULT init();
	void release();
	void update();
	void render();

	//왼손
	void leftMove();
	void changeLeftDirection(BOSSLEFTDIRECTION leftDirection);
	static void CBleftAttack(void* obj);

	//머리통
	void headMove();
	void changeHeadDirection(BOSSHEADDIRECTION headDirection);
	static void CBheadAttack(void* obj);

	//콜백함수
	
	//왼손
	BOSSLEFTDIRECTION getLeftDirection() { return _bossLeftDirection; }
	void setLeftDirection(BOSSLEFTDIRECTION leftDirection) { _bossLeftDirection = leftDirection; }

	animation* getLeftMotion0() { return _bossMotion[0]; }
	void setLeftMotion0(animation* ani) { _bossMotion[0] = ani; }

	//머리통
	BOSSHEADDIRECTION getHeadDirection() { return _bossHeadDirection; }
	void setHeadDirection(BOSSHEADDIRECTION headDirection) { _bossHeadDirection = headDirection; }

	animation* getHeadMotion1() { return _bossMotion[1]; }
	void setHeadMotion1(animation* ani) { _bossMotion[1] = ani; }
};

