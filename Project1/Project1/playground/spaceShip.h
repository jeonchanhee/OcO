#pragma once
#include "gameNode.h"
#include "bullets.h"
#include "progressBar.h"

//이게 최선입니까? 최선이에요?! 
#pragma warning(disable:4996)

//상호참조를 위한 전방선언 (빌드 속도도 업 ㅇ _ㅇ)b )
class enemyManager;

class spaceShip : public gameNode
{
private:
	image* _ship;		//우주선 이미지 
	missile* _missile;	//미사일 클래스
	minho* _hoooo;

	enemyManager* _em;

	progressBar* _hpBar;		//스페이스 쉽 HP바
	float _currentHP, _maxHP;	//현재체력 / 최대체력

	int _alphaValue;

public:
	spaceShip();
	~spaceShip();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void collision();

	//피격 시 HP 깍아주는 함수
	void hitDamage(float damage);

	image* getShipImage() { return _ship; }

	void setEmMemoryAddressLink(enemyManager* em) { _em = em; }

	minho* getMinho() { return _hoooo; }

};

