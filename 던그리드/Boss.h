#pragma once
#include "Enemy.h"

#define HANDSPEED 3.0f

enum BOSSHEADDIRECTION
{
	BOSS_HEAD_IDLE,
	BOSS_HEAD_ATTACK,
	BOSS_HEAD_DIE
};

enum BOSSRHANDDIRECTION
{
	BOSS_RIGHT_IDLE,
	BOSS_RIGHT_MOVE,
	BOSS_RIGHT_LASER
};

enum BOSSLHANDDIRECTION
{
	BOSS_LEFT_IDLE,
	BOSS_LEFT_MOVE,
	BOSS_LEFT_LASER
};

struct tagBoss
{
	RECT rc;
	image* img;
	float x, y;
};

class Boss : public Enemy
{
	BOSSHEADDIRECTION _bossHeadDirection;
	BOSSRHANDDIRECTION _bossRHandDirection;
	BOSSLHANDDIRECTION _bossLHandDirection;

	animation* _bossMotion[3]; //0왼손.1머리.2오른손
	tagBoss _bossComponent[3]; //0왼손.1머리.2오른손

public:
	Boss();
	~Boss();

	HRESULT init();
	void release();
	void update();
	void render();

	void leftHandMove();
	void headMove();
	void rightHandMove();

	void changeHeadAnimation(BOSSHEADDIRECTION head);
	void changeLHandAnimation(BOSSLHANDDIRECTION LHand);
	void changeRHandAnimation(BOSSRHANDDIRECTION RHand);

	static void headAttack(void* obj);
	static void handRightLaser(void* obj);
	static void handLeftLaser(void* obj);

	//콜백함수
	BOSSHEADDIRECTION getBossHeadDirection() { return _bossHeadDirection; }
	void setBossHeadDirection(BOSSHEADDIRECTION headDirection) { _bossHeadDirection = headDirection; }

	BOSSLHANDDIRECTION getBossLHandDirection() { return _bossLHandDirection; }
	void setBossLHandDirection(BOSSLHANDDIRECTION LHandDirection) { _bossLHandDirection = LHandDirection; }

	BOSSRHANDDIRECTION getBossRHandDirection() { return _bossRHandDirection; }
	void setBossRHandDirection(BOSSRHANDDIRECTION RHandDirection) { _bossRHandDirection = RHandDirection; }
	 
	//왼손
	animation* getBossMotion1() { return _bossMotion[0]; }
	void setBossMotion1(animation* ani) { _bossMotion[0] = ani; }

	//머리
	animation* getBossMotion2() { return _bossMotion[1]; }
	void setBossMotion2(animation* ani) { _bossMotion[1] = ani; }

	//오른손
	animation* getBossMotion3() { return _bossMotion[2]; }
	void setBossMotion3(animation* ani) { _bossMotion[2] = ani; }
};

