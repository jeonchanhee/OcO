#pragma once
#include "Enemy.h"
#include "progressBar.h"

enum REDBATDIRECTION
{
	REDBAT_RIGHT_MOVE,
	REDBAT_LEFT_MOVE,
	REDBAT_RIGHT_ATTACK,
	REDBAT_LEFT_ATTACK,
	REDBAT_RIGHT_DIE,
	REDBAT_LEFT_DIE
};

class RedBat : public Enemy
{
	progressBar* _progressBar;
	float _currentHP, _maxHP;

	REDBATDIRECTION _redBatDirection;
	animation* _redBatMotion;
	
	float _startX, _startY;

public:
	RedBat();
	~RedBat();

	HRESULT init(float x, float y);
	void release();
	void update();
	void render();

	void move();
	void rightMove();
	void leftMove();

	void Attack();
	
	void changeAnimation(REDBATDIRECTION direction);


	static void rightAttack(void* obj);
	static void leftAttack(void* obj);

	//콜백함수
	REDBATDIRECTION getRedBatDirection() { return _redBatDirection; }
	void setRedBatDirection(REDBATDIRECTION dir) { _redBatDirection = dir; }

	animation* getRedBatMotion() { return _redBatMotion; }
	void setRedBatMotion(animation* ani) { _redBatMotion = ani; }

	void playerCollision();
	void hitDamage(float damage);

	int getCurrentHp() { return _currentHP; } //현재 hp
	int getMaxHp() { return _maxHP; } //전체hp
	void setCurrentHp(int currentHP) { _currentHP = currentHP; }
	void setMaxHp(int maxHP) { _maxHP = maxHP; }
	RECT  getRedBatRect() { return _rc; } //rc
};

