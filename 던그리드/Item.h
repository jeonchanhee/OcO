#pragma once
#include "gameNode.h"


enum ITEMGRADE //아이템 등급
{
	NORMAL,		// 노말
	RARE,		// 레어 
	LEGENDARY	// 전설
};

enum ITEMTYPE // 아이템의 타입
{
	WEAPON,						// 무기
	SWORD, HAMMER, GUN, BOW,	// 검, 해머 ,총 , 활
	ARMOR,						// 아머
	SHIELD,						// 방패
	SECOND_EQUIPMENT,			// 보조장비 
	ACCESSORY,					// 액세서리
	FOOD,						// 음식
	GOLD,						// 코인 / 골드바
};

enum ITEMCONDITION
{
	DROPITEM,	// 드랍아이템인지 
	INVENITEM,	// 인벤토리 안에 있는 아이템 인지.
	WEARITEM,	// 착용아이템인지
};

struct tagItem // 아이템
{
	image* image[13];			// 0.드랍 1.인벤 2. 착용
	RECT rc[13];					// 렉트
	ITEMTYPE type;				// 아이템 종류
	ITEMGRADE grade;			// 아이템 등급
	float x, y;					//x, y 좌표
	bool isFrame;				// 프레임 이미지 인지 아닌지 확인
	bool sellBan;				// 판매금지 아이템 인지 아닌지
	int frameX, frameY;			//프레임 X, Y
	int minimumAtt, MaxAtt;		//최소 ~ 최대 공격력 20 ~ 30 이면 고정딜은 22정도?
	int ad;						//공격력
	int fixedDamage;			//고정딜 22;
	float attackSpeed;			//공격속도	
	float moveMentSpeed;		//이동속도
	float criticalPersent;		//크리티컬확률
	float evasionPersent;		//회피율
	float hpRecovery;			//hp회복
	float dashPower;			//대시공격력 증감률 
	int addMaxHp;				//최대 HP 증가
	int price;					//가격 ?? 상점에서 살때 3천원이라고하면 팔때는 X 0.2 해서 600 이런식으로 가격책정
};


class Item : public gameNode
{
private:
	ITEMCONDITION _condition;
	bool _isDropItem; // 드랍아이템인지 아닌지 확인
	bool _isInvenItem; // 인벤토리에 착용하고 있는 아이템 인지 아닌지 확인
	bool _isWearItem; // 화면 안에서 영웅이 착용하고 있는 이미지 인지 아닌지 확인
	
	
public:
	Item();
	~Item();

	HRESULT init();
	void release();
	void update();
	void render();

	void ItemDirection();

	void setDropItem();
	void setInvenItem();
	void setWearItem();


	



};
