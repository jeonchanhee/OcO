#pragma once
#include "Item.h"
#include "gameNode.h"



class itemManager : public gameNode
{
private:
	typedef vector <Item*> Vitem;
	typedef vector <Item*>::iterator VIitem;

	Item inven[23];

private:
	Vitem _vItem;
	VIitem _viItem;
	
	Item* item;

	image* _image;
	
	bool _isFrame;

	
public:
	itemManager();
	~itemManager();

	vector <Item*> getItem() { return _vItem; }

	HRESULT init();
	void release();
	void update();
	void render();

	void CreateWeapon(bool frame);																						// 무기 생성
	void CreateDefenceMechanism(ITEMTYPE type, const char* itemName, int value, int num, bool frame);	// 방어구 생성
	void CreateSecondEquipment(ITEMTYPE type, const char* itemName, int value, int num, bool frame);	// 보조장비 생성
	void CreateAccessory(ITEMTYPE type, const char* itemName, int value, int num, bool frame);			// 악세서리 생성
	void CreateFood(ITEMTYPE type, const char* itemName, int value, int num, bool frame);				// 음식 생성 
	void CreateTreasureBox(ITEMTYPE type, const char* itemName, int value, int num, bool frame);		// 보물상자 생성
	void CreateGold(ITEMTYPE type, const char* itemName, int value, int num, bool frame);				// 골드 생성

	

	// 아이템 벡터 접근자
	vector<Item*>			getvItem()	{ return _vItem; }
	vector<Item*>::iterator getviItem()	{ return _viItem; }
};

