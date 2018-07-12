#pragma once
#include "Enemy.h"

enum REDBATDIRECTION
{
	REDBAT_RIGHT_MOVE,
	REDBAT_LEFT_MOVE,
	REDBAT_RIGHT_UP_MOVE,
	REDBAT_LEFT_UP_MOVE,
	REDBAT_RIGHT_DOWN_MOVE,
	REDBAT_LEFT_DOWN_MOVE,
	REDBAT_UP_MOVE,
	REDBAT_DOWN_MOVE,
	REDBAT_RIGHT_ATTACK,
	REDBAT_LEFT_ATTACK,
	REDBAT_RIGHT_DIE,
	REDBAT_LEFT_DIE
};

class RedBat : public Enemy
{
	REDBATDIRECTION _redBatDirection;
	animation* _redBatMotion;
	RECT rcCollision;	// Ÿ�� ���� ��Ʈ

	float _startX, _startY;
	bool _isAtteck;
	int		randNum;	// �����̵�
	int		_moveCount;

	bool _diedie;
	int _dieCount;

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

	static void redBatDieMotion(void * obj);
	
	void changeAnimation(REDBATDIRECTION direction);
	void die();


	static void rightAttack(void* obj);
	static void leftAttack(void* obj);

	//�ݹ��Լ�
	REDBATDIRECTION getRedBatDirection() { return _redBatDirection; }
	void setRedBatDirection(REDBATDIRECTION dir) { _redBatDirection = dir; }

	animation* getRedBatMotion() { return _redBatMotion; }
	void setRedBatMotion(animation* ani) { _redBatMotion = ani; }

	void playerCollision();
	void hitDamage();
	//void hitDamage(float damage);

	int getCurrentHp() { return _currentHP; } //���� hp
	int getMaxHp() { return _maxHP; } //��ühp
	void setCurrentHp(int currentHP) { _currentHP = currentHP; }
	void setMaxHp(int maxHP) { _maxHP = maxHP; }
	RECT  getRedBatRect() { return _rc; } //rc

	bool getisAtteck() { return _isAtteck; }
	void setisAtteck(bool isAtteck) { _isAtteck = isAtteck; }

	//REDBATDIRECTION getredBatDirection() { return _redBatDirection; }
};

