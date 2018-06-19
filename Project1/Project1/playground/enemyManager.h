#pragma once
#include "gameNode.h"
#include "minion.h"
#include "bullets.h"
#include <vector>

//클래스 전방선언 (상호참조를 위해)(컴파일 속도를 높이기 위해)
class spaceShip;

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*>				vEnemy;
	typedef vector<enemy*>::iterator	viEnemy;

private:
	vEnemy	_vMinion;	//적 담아서 관리할 벡터
	viEnemy _viMinion;	//벡터친구 이터레이터

	bullet* _bullet;

	spaceShip* _ship;
public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//적 생성함수
	void setMinion(void);

	void minionBulletFire();

	void removeMinion(int arrNum);

	void collision();

	

	//빈 클래스포인터에 원래 주소지를 넣어주는
	void setSpaceShipMemoryAddressLink(spaceShip* ship) { _ship = ship; }

	//미니언 벡터 접근자
	vector<enemy*> getVMinion() { return _vMinion; }
	vector<enemy*>::iterator getVIMinion() { return _viMinion; }
};

