#pragma once
#include "Enemy.h"
#include "Bullet.h"
#include "progressBar.h"

enum BIGBATDIRECTION
{
	BIGBAT_RIGHT_MOVE,
	BIGBAT_LEFT_MOVE,
	BIGBAT_RIGHT_ATTACK,
	BIGBAT_LEFT_ATTACK,
	BIGBAT_RIGHT_DIE,
	BIGBAT_LEFT_DIE
};

class BigBat : public Enemy
{
	progressBar* _progressBar;
	float _currentHP, _maxHP;

	BIGBATDIRECTION _bigBatDirection;
	animation* _bigBatMotion;
	Bullet* _bullet;

	bool _isAttack;
public:
	BigBat();
	~BigBat();

	HRESULT init(float x, float y);
	void release();
	void update();
	void render();

	void attackMove();
	void changeAnimation(BIGBATDIRECTION direction);
	void bulletfire();

	static void rightAttack(void* obj);
	static void leftAttack(void* obj);

	//콜백함수
	BIGBATDIRECTION getBigBatDirection() { return _bigBatDirection; }
	void setBigBatDirection(BIGBATDIRECTION dir) { _bigBatDirection = dir; }

	animation* getBigBatMotion() { return _bigBatMotion; }
	void setBigBatMotion(animation* ani) { _bigBatMotion = ani; }
	
	bool getisAtteck() { return _isAttack; }
	void setisAtteck(bool isAttack) { _isAttack = isAttack; }


	void playerCollision();
	void hitDamage(float damage);
};

