#pragma once
#include "Item.h"



struct tagWeapon // 무기 구조체~~
{
	image* image[3];			// 0.드랍 1.인벤 2. 착용
	RECT rc[3];					// 렉트
	ITEMTYPE type;				// 무기의 종류
	ITEMGRADE grade;			// 무기의 등급
	float x, y;					//x, y 좌표
	bool isFrame;				// 프레임 이미지 인지 아닌지 확인
	bool sellBan;				// 판매금지 아이템 인지 아닌지
	int frameX, frameY;			//프레임 X, Y
	int minimumAtt, MaxAtt;		//최소 ~ 최대 공격력 20 ~ 30 이면 고정딜은 22정도?
	int fixedDamage;			//고정딜 22;
	float attackSpeed;			//공격속도	
	float moveMentSpeed;		//이동속도
	float criticalPersent;		//크리티컬확률
	float evasionPersent;		//회피율
	float dashPower;			//대시공격력 증감률 
	int addMaxHp;				//최대 HP 증가
	int price;					//가격 ?? 상점에서 살때 3천원이라고하면 팔때는 X 0.2 해서 600 이런식으로 가격책정
};


class Weapon :	public Item
{
private:

	tagWeapon _weapon;
	int _count;

	const char* _weaponName;
	int _value;
	
public:
	Weapon();
	~Weapon();

	HRESULT init(ITEMTYPE type, const char* weaponName, int value, POINT position);
	void release();
	void update();
	void render();

	void CreateWeapon(ITEMTYPE type, const char* weaponName, int value);
	void setSword(const char* weaponName, int value);
	void setHammer(const char * weaponName, int value);
	void setGun(const char * weaponName, int value);
	void setBow(const char * weaponName, int value);



};

