#pragma once
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Shield.h"
#include "SecondEquipment.h"
#include "Accessory.h"
#include "Food.h"
#include "gameNode.h"



class itemManager : public gameNode
{
private:
	typedef vector <Item*>							vItem; 
	typedef vector <Item*>::iterator				viItem;


private:

	vItem  _vItem;
	viItem _viItem;
	

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

