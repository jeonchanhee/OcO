#pragma once
#include "gameNode.h"


enum ITEMTYPE // 아이템의 타입
{
	SHORT_DISTANCE_WEAPON,	// 근접무기
	LONG_DISTANCE_WEAPON,	// 원거리 무기
	DEFENCE_MECHANISM,		// 방어구
	SECOND_EQUIPMENT,		// 보조장비 
	ACCESSORY,				// 액세서리
	CONSUME,				// 소비되는 모든 아이템(음식)
	HEALING,				// 힐링
	TREASUREBOX,			// 보물박스
	GOLD,					// 코인 / 골드바
};

enum IMAGETYPE
{
	단일, 프레임
};

struct tagItem // 아이템 구조체~~
{
	image* image[3];		//이미지 0배열 : 떨궛을때 1 : 배열 인벤토리에서볼때 2배열 :장착했을땐데  (이것만프레임있는지 bool준다)
	ITEMTYPE type;			//d아이템무슨타입??
	IMAGETYPE imagetype;	// 이미지타입.
	RECT rc;				// 렉트
	const char* imageName;  //이미지의 이름(아이템이름)
	float x, y;				//x, y 좌표
	bool isFrame;			//bool 값 프레임인가 ??
	int frameX, frameY;		//프레임 X, Y
	int ad;					//공격력
	int armor;				//방어력	
	float attackSpeed;		//공격속도
	float moveMentSpeed;	//이동속도	
	float criticalPersent;	//크리티컬확률
	float evasionPersent;	//회피율
	float dashPower;		//대시공격력 증감률 
	int addMaxHp;			//최대 HP 증가
	int heal;				//힐
	int fullNess;			//공복도 어느정도 ? food일때만 ㅇㅋ??
	int fixedDamage;		//고정딜 
	int gold;				// 골드 랜덤으로 돌릴거 ㅇㅇ
	int price;				//가격 ?? 상점에서 살때 3천원이라고하면 팔때는 X 0.2 해서 600 이런식으로 가격책정
	bool isfly;				// 날고있니?
};


class Item : public gameNode
{
private:
	tagItem _item;
	int _count;
	int _num;
public:

	HRESULT init();
	void release();
	void update();
	void render();

					//아이템 타입      //이미지 타입         //아이템 번호  // 프레임 이미지인가? // x,y 좌표
	void createItem(ITEMTYPE type, IMAGETYPE type2, const char* itemName, int value, int num, bool frame);
	
	void LongDistanceWeapon(const char* imageName, int value, int num);		// 원거리 무기
	void ShortDistanceWeapon(const char* imageName, int value, int num);	// 근거리 무기
	void DefenceMechanism(const char* imageName, int value, int num);		// 방어구
	void SecondEquipment(const char* imageName, int value, int num);		// 보조장비
	void Accessory(const char* imageName, int value, int num);				// 악세사리
	void Consume(const char* imageName, int value, int num);				// 소비아이템
	void Healing(const char* imageName, int value, int num);				// 힐링요정~
	void TreasureBox(const char* imageName, int value, int num);			// 보물박스(여기서 골드 / 아이템이 나옴)
	void Gold(const char* imageName, int value, int num);					// 코인 / 골드바



	IMAGETYPE getimageType() { return _item.imagetype; }


};
