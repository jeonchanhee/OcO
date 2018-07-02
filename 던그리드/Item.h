#pragma once
#include "gameNode.h"


enum ITEMTYPE // 아이템의 타입
{
	SHORT_ATTACK,	// 근접무기
	LONG_ATTACK,	// 원거리 무기
	SECOND_EQUIPMENT, // 보조장비 
	ACCESSORY,		// 액세서리
	FOOD,			// 음식
	HEALING,		// 힐링
	TREASUREBOX,	// 보물박스
	GOLD			// 코인 / 골드바
};


struct tagItem
{
	image* image[3];		//이미지 0배열 : 떨궛을때 1 : 배열 인벤토리에서볼때 2배열 :장착했을땐데  (이것만프레임있는지 bool준다)
	ITEMTYPE type;			//d아이템무슨타입??
	RECT rc;				// 렉트
	bool isFrame;			//bool 값 프레임인가 ??
	int ad;					//공격력
	int armor;				//방어력	
	int attackSpeed;		//공격속도
	float moveMentSpeed;	//이동속도	
	float criticalPersent;	//크리티컬확률
	float dashPower;		//대시공격력 증감률 
	int addMaxHp;			//최대 HP 증가
	int fullNess;			//공복도 어느정도 ? food일때만 ㅇㅋ??
	int evasionPersent;		//회피율 
	int fixedDamage;		//고정딜 
	int price;				//가격 ?? 상점에서 살때 3천원이라고하면 팔때는 X 0.2 해서 600 이런식으로 가격책정
};


class Item : public gameNode
{
private:

	vector<tagItem>				_vItem;
	vector<tagItem>::iterator	_viItem;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	void createItem(int value , ITEMTYPE type , bool frame);
	



	vector<tagItem>				getvItem()		{ return _vItem; }
	vector<tagItem>::iterator	getviItem()		{ return _viItem; }
};
