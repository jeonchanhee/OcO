#pragma once
#include "gameNode.h"
#include "MusicAngel.h"
#include "BigBat.h"
#include "DogBone.h"
#include "Cow.h"
#include "Arrow.h"
#include "BigRedBat.h"
#include "RedBat.h"
#include "BigBat.h"
#include "Bat.h"
#include "Boss.h"
#include <vector>

class EnemyManager : public gameNode
{
private:
	typedef vector<Enemy*>	vEnemy;
	typedef vector<Enemy*>::iterator viEnemy;

	vEnemy _vMonster;
	viEnemy _viMonster;

public:
	EnemyManager();
	~EnemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setMonster();

	//몬스터 접근자
	vector<Enemy*> getVMonster() { return _vMonster; }
	vector<Enemy*>::iterator getVIMonster() { return _viMonster; }

};

