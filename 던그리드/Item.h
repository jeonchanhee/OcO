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
	const char* name;			// 이름
	image* image[3];			// 0.드랍 1.인벤 2. 착용
	RECT rc[3];					// 렉트
	ITEMTYPE type;				// 아이템 종류
	ITEMGRADE grade;			// 아이템 등급
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

	HRESULT init(ITEMTYPE type, const char * itemName, int value, POINT position);
	void release();
	void update();
	void render();
	void invenRender(HDC hdc, int x, int y);


	void CreateItem(ITEMTYPE type, const char* itemName, int value); // 아이템 만드러줌
	
	void setSword(const char* weaponName, int value);				// 검 정의해줌
	void setHammer(const char * weaponName, int value);				// 해머 정의해줌
	void setGun(const char * weaponName, int value);				// 총 정의해줌
	void setBow(const char * weaponName, int value);				// 활 정의해줌
	void setArmor(const char* ArmorName, int value);				// 아머 정의해줌
	void setShield(const char* ShieldName, int value);				// 쉴드 정의해줌
	void setEquip(const char* secondEquipment, int value);			// 보조장비 정의해줌
	void setAccessory(const char* AccessoryName, int value);		// 악세 정의해줌
	void setFood(const char* FoodName, int value);					// 음식 정의해줌

	ITEMTYPE getItemType() { return _item.type; }
	image * equipmentImage() { return _item.image[2]; }
	tagItem getItem() { return _item; }
	



};
