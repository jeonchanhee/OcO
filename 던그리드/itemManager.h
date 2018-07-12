#pragma once
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Shield.h"
#include "SecondEquipment.h"
#include "Accessory.h"
#include "Food.h"
#include "WeaponNpc.h"
#include "FoodNpc.h"
#include "gameNode.h"
#include "Player.h"

class itemManager : public gameNode
{
private:
	typedef vector <Item*>							vItem; 
	typedef vector <Item*>::iterator				viItem;


private:
	WeaponNpc * _weaponNpc;
	FoodNpc * _foodNpc;
	vItem  _vItem;
	viItem _viItem;
	Player* _player;
	//inven 
	bool _showInven;
	char _isSelect;
	RECT _selectRect[15];
	//인벤토리에 집어넣기 빼기 장착하기 해체하기 ;
public:
	itemManager();
	~itemManager();

	vector <Item*> getItem() { return _vItem; }

	HRESULT init();
	void release();
	void update();
	void render();

	void CreateItem();		





	// 아이템 벡터 접근자

	vector<Item*>			getvItem()	{ return _vItem; }
	vector<Item*>::iterator getviItem()	{ return _viItem; }
};

