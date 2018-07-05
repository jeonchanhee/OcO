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
