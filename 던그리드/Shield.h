#pragma once
#include "Item.h"


struct tagShield // 방패 구조체~~
{
	image* image[3];		//이미지 0. 드랍 1. 인벤 2. 착용
	RECT rc[3];				//렉트
	ITEMTYPE type;			//아이템 타입
	ITEMGRADE grade;		//아이템 등급
	const char* imageName;  //이미지의 이름(아이템이름)
	float x, y;				//x, y 좌표
	int ad;					//공격력
	int def;				//방어력	
	float attackSpeed;		//공격속도
	float moveMentSpeed;	//이동속도
	float dashPower;		//대시공격력 증감률
	float criticalPersent;	//크리티컬확률
	float evasionPersent;	//회피율
	int addMaxHp;			//최대 HP 증가
	int price;				//가격 ?? 상점에서 살때 3천원이라고하면 팔때는 X 0.2 해서 600 이런식으로 가격책정
};


class Shield : public Item
{
private:
	tagShield _shield;

	const char* _ShieldName;
	int _value;
public:
	Shield();
	~Shield();

	HRESULT init(ITEMTYPE type, const char* ShieldName, int value, POINT position);
	void release();
	void update();

	void CreateShield(ITEMTYPE type, const char* ShieldName, int value);
	void setShield(const char* ShieldName, int value);
	void render();

};

