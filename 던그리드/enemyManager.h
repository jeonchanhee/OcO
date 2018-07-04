#pragma once
#include "gameNode.h"
#include "Bullet.h"
#include "progressBar.h"
#include "MusicAngel.h"
#include "BigBone.h"
#include "DogBone.h"
#include "Cow.h"
#include "Arrow.h"
#include "BigRedBat.h"
#include "RedBat.h"
#include "BigBat.h"
#include "Bat.h"
#include "Boss2.h"

class EnemyManager : public gameNode
{
private:
	typedef vector<Enemy*>	vEnemy;
	typedef vector<Enemy*>::iterator viEnemy;

	vEnemy _vMonster;
	viEnemy _viMonster;

	Bullet* _bullet;
	progressBar* _hpBar;

	float _currentHP, _maxHP;
	int _count;

public:
	EnemyManager();
	~EnemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	
	void setMonster(); //몬스터 생성 함수
	//void hitDamage(); //HP깎는 함수
	//void monsterBulletFire();
	//void removeMonster();
	//bool isFinish();
	
	

	//몬스터 접근자
	vector<Enemy*> getVMonster() { return _vMonster; }
	vector<Enemy*>::iterator getVIMonster() { return _viMonster; }

};

