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
	//�κ��丮�� ����ֱ� ���� �����ϱ� ��ü�ϱ� ;
public:
	itemManager();
	~itemManager();

	vector <Item*> getItem() { return _vItem; }

	HRESULT init();
	void release();
	void update();
	void render();

	void CreateItem();		





	// ������ ���� ������

	vector<Item*>			getvItem()	{ return _vItem; }
	vector<Item*>::iterator getviItem()	{ return _viItem; }
};

