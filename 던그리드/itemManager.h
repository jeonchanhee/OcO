#pragma once
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Shield.h"
#include "SecondEquipment.h"
#include "Accessory.h"

#include "gameNode.h"



class itemManager : public gameNode
{
private:
	typedef vector <Item*>							vItem; // 전체 아이템 드랍아이템인지 인벤토리 안에 있는 아이템인지, 착용하고 있는지 확인용 ㅇ
	typedef vector <Item*>::iterator				viItem;

	typedef vector <Weapon*>						vWeapon; // 무기전체를 담은 벡터
	typedef vector <Weapon*>::iterator				viWeapon;

	typedef vector <Armor*>							vArmor; // 아머 전체를 담은 벡터
	typedef vector <Armor*>::iterator				viArmor;

	typedef vector <Shield*>						vShield; // 방패 전체를 담은 벡터
	typedef vector <Shield*>::iterator				viShield;

	typedef vector <SecondEquipment*>				vSecond; // 보조장비 전체를 담은 벡터
	typedef vector <SecondEquipment*>::iterator		viSecond;

	typedef vector <Accessory*>						vAccessory; //  악세서리 전체를 담은 벡터
	typedef vector <Accessory*>::iterator			viAccessory;

private:

	vItem  _vItem;
	viItem _viItem;
	
	vWeapon _vWeapon;
	viWeapon _viWeapon;

	vArmor _vArmor;
	viArmor _viArmor;

	vShield _vShield;
	viShield _viShield;

	vSecond _vSecond;
	viSecond _viSecond;

	vAccessory _vAccessory;
	viAccessory _viAccessory;


public:
	itemManager();
	~itemManager();

	vector <Item*> getItem() { return _vItem; }

	HRESULT init();
	void release();
	void update();
	void render();

	void CreateItem();																						// 무기 생성

	// 아이템 벡터 접근자

	vector<Item*>			getvItem()	{ return _vItem; }
	vector<Item*>::iterator getviItem()	{ return _viItem; }
};

