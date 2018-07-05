#pragma once
#include "Item.h"


struct tagSecondEquipment // 보조장비 구조체~~
{
	image* image[3];		//이미지 0. 드랍 1. 인벤 2. 착용
	RECT rc[3];				//렉트
	ITEMTYPE type;			//아이템 타입
	ITEMGRADE grade;		//아이템 등급
	int frameX, frameY;		// 프레임 X, Y
	bool isFrame;			// 프레임이미지 확인용
	float x, y;				//x, y 좌표
	int ad;					// 공격력
	int def;				//방어력	
	float attackSpeed;		//공격속도
	float moveMentSpeed;	//이동속도	
	float criticalPersent;	//크리티컬확률
	float evasionPersent;	//회피율
	int addMaxHp;			//최대 HP 증가
	int price;				//가격 ?? 상점에서 살때 3천원이라고하면 팔때는 X 0.2 해서 600 이런식으로 가격책정
};


class SecondEquipment : public Item
{
private:

	tagSecondEquipment _second;

	int _count;
public:

	SecondEquipment();
	~SecondEquipment();

	HRESULT init();
	void release();
	void update();
	void render();


	void CreateEquipment(ITEMTYPE type, const char* secondEquipmentName, int value, POINT position);
	void setEquip(const char* secondEquipment, int value);
};

