#pragma once
#include "gameNode.h"


enum ITEMGRADE //아이템 등급
{
	NORMAL,		// 노말
	RARE,		// 레어 
	LEGENDARY	// 전설
};

enum PROPERTYTYPE
{
	COIN,
	GOLDBAR
};

enum ITEMTYPE // 아이템의 타입
{
	SWORD, HAMMER, GUN, BOW,	// 검, 해머 ,총 , 활
	ARMOR,						// 아머
	SHIELD,						// 방패
	SECOND_EQUIPMENT,			// 보조장비 
	ACCESSORY,					// 액세서리
	FOOD,						// 음식

};



enum DROPITEM // 드랍아이템
{
	DR_SWORD, DR_HAMMER, DR_GUN, DR_BOW,			// 드랍아이템이 검 / 해머 / 총 / 활 일때
	DR_ARMOR, DR_SHIELD, DR_SECOND, DR_ACCESSORY,	// 드랍아이템이 아머 / 방패 / 보조 장비 / 악세서리 일 때
	DR_COIN, DR_GOLDBAR								// 드랍아이템이 코인 / 골드바 일 때
};

enum INVENITEM // 인벤에 있는 아이템
{
	IV_SWORD, IV_HAMMER, IV_GUN, IV_BOW,			// 인벤에 있는 아이템이 검 / 해머 / 총 / 활 일 때
	IV_ARMOR, IV_SHIELD, IV_SECOND, IV_ACCESSORY,	// 인벤에 있는 아이템이 아머 / 방패 / 보조 장비 / 악세서리 일 때
	IV_COIN											// 인벤이 있는 아이템이 코인일 때
};

enum WEARITEM
{
	WR_SWORD, WR_HAMMER, WR_GUN, WR_BOW,			// 착용한 아이템이 검 / 해머 / 총 / 활 일 때
	WR_SECOND										// 착용한 아이템이 보조 장비 일 때
};

struct tagproperty
{
	image* image;		// 이미지
	RECT rc;			// 렉트
	PROPERTYTYPE type;	// 코인이냐 골드바냐
	float x, y;			// x, y 좌표
	bool isFrame;		// 프레임 이미지냐
	int frameX, frameY; // 프레임 X,Y
	int value;			// 얼마냐

};

struct tagItem // 아이템
{
	image* image[3];			// 0.드랍 1.인벤 2. 착용
	RECT rc[3];					// 렉트
	ITEMTYPE type;				// 아이템 종류
	ITEMGRADE grade;			// 아이템 등급
	DROPITEM drop;				// 드랍아이템 일때
	INVENITEM inven;			// 인벤아이템 일때
	WEARITEM wear;				// 착용아이템 일때
	float x, y;					//x, y 좌표
	bool isFrame;				// 프레임 이미지 인지 아닌지 확인
	bool sellBan;				// 아이템 판매금지 시킬때
	int frameX, frameY;			//프레임 X, Y
	int minimumAtt, MaxAtt;		//최소 ~ 최대 공격력 20 ~ 30 이면 고정딜은 22정도?
	int fixedDamage;			//고정딜 22;
	int ad;						//공격력 증가
	int def;					//방어력 증가					
	float attackSpeed;			//공격속도 
	float moveMentSpeed;		//이동속도 
	float criticalPersent;		//크리티컬확률 증가
	float evasionPersent;		//회피율 
	float hpRecovery;			//hp회복 
	float dashPower;			//대시공격력 증감률 
	int addMaxHp;				//최대 HP 증가
	int price;					//가격 
	const char* name;			// 이름
	int value;					// 숫자받기위해씀

};

class Item : public gameNode
{
private:

	tagItem _item;
	int _count;
	
	
public:
	Item();
	~Item();

	HRESULT init(ITEMTYPE type, const char* itemName, int value, POINT position);
	void release();
	void update();
	void render();


	void CreateItem(ITEMTYPE type, const char* itemName, int value); // 아이템 만들어줌
	void setSword(const char* weaponName, int value);			// 검 정의해줌
	void setHammer(const char * weaponName, int value);			// 해머 정의해줌
	void setGun(const char * weaponName, int value);			// 총 정의해줌
	void setBow(const char * weaponName, int value);			// 활 정의해줌
	void setArmor(const char* ArmorName, int value);			// 아머 정의해줌
	void setShield(const char* ShieldName, int value);			// 쉴드 정의해줌
	void setEquip(const char* secondEquipment, int value);		// 보조장비 정의해줌
	void setAccessory(const char* AccessoryName, int value);	// 악세 정의해줌
	void setFood(const char* FoodName, int value);				// 음식 정의해줌

	tagItem getItem() { return _item; }
	
	//void dropItem(DROPITEM type, const char* dropItem, int value);			// 드랍 아이템 만들어줌
	//void setDropItem(const char* dropItem, int value);						// 드랍아이템 정의해줌


	//void invenItem(INVENITEM type, const char* invenItem, int value);		// 인벤아이템 만들어줌							
	//void setInvenItem(const char* invenItem, int value);					// 인벤토리에 무기를 소지하고 있을 때 or 인벤토리 안에서 착용 하고 있을 때


	//void wearItem();				// 착용아이템 만들어줌
	//void wearWeapon();				// 무기를 착용하고 있을때
	//void wearsecond();				// 보조장비를 착용하고 있을 때

	//void storeItem();				// 상점 아이템 만들어줌~~
	//void setIfStoreItemIsWeapon();	// 상점에서 팔고 있는 아이템이 무기일 때
	//void setIfStoreItemIsDefence();	// 상점에서 팔고 있는 아이템이 방어구 일 때
	//void setIfStoreItemIsFood();	// 상점에서 팔고 있는 아이템이 음식일 때



};
