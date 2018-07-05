#pragma once
#include "Enemy.h"

#define BOSSSPEED 3.0f

//보스 머리통 방향
enum BOSSHEADDIRECTION
{
	HEAD_IDLE,
	HEAD_ATTACK,
	HEAD_DIE
};

//왼손꾸락 방향
enum BOSSLEFTDIRECTION
{
	LEFT_IDLE,
	LEFT_UP_MOVE,
	LEFT_DOWN_MOVE,
	LEFT_LASER
};

//오른손꾸락 방향
enum BOSSRIGHTDIRECTION
{
	RIGHT_IDLE,
	RIGHT_UP_MOVE,
	RIGHT_DOWN_MOVE,
	RIGHT_LASER
};

//보스의 구조체
struct tagBoss
{
	RECT rc;
	image* img;
	float x, y;
};

class Boss2 : public Enemy
{
private:
	tagBoss _boss[3]; //보스의 머리,왼손,오른손이 있는 구조체변수
	
	BOSSHEADDIRECTION _bossHeadDirection;
	BOSSLEFTDIRECTION _bossLeftDirection;
	BOSSRIGHTDIRECTION _bossRightDirection;

	animation* _bossMotion[3]; //0왼손.1머리.2오른손
	

public:
	Boss2();
	~Boss2();

	HRESULT init();
	void release();
	void update();
	void render();

	//왼손
	void leftMove(); //왼손 움직이게 하는 함수
	void changeLeftDirection(BOSSLEFTDIRECTION leftDirection); //방향바꿔주는 함수
	static void CBleftAttack(void* obj); 

	//머리통
	void headMove(); //머리통 움직이게 하는 함수
	void changeHeadDirection(BOSSHEADDIRECTION headDirection); //방향바꿔주는 함수
	static void CBheadAttack(void* obj); 

	//오른손
	void rightMove(); //오른손 움직이게 하는 함수
	void changeRightDirection(BOSSRIGHTDIRECTION rightDirection); //방향바꿔주는 함수
	static void CBrightAttack(void* obj);


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

	//오른손
	BOSSRIGHTDIRECTION getRightDirection() { return _bossRightDirection; };
	void setRightDirection(BOSSRIGHTDIRECTION rightDirection) { _bossRightDirection = rightDirection; }

	animation* getRightMotion2() { return _bossMotion[2]; }
	void setRightMotion2(animation* ani) { _bossMotion[2] = ani; }
};

