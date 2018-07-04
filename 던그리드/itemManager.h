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

	void CreateWeapon(bool frame);																						// ���� ����
	void CreateDefenceMechanism(ITEMTYPE type, const char* itemName, int value, int num, bool frame);	// �� ����
	void CreateSecondEquipment(ITEMTYPE type, const char* itemName, int value, int num, bool frame);	// ������� ����
	void CreateAccessory(ITEMTYPE type, const char* itemName, int value, int num, bool frame);			// �Ǽ����� ����
	void CreateFood(ITEMTYPE type, const char* itemName, int value, int num, bool frame);				// ���� ���� 
	void CreateTreasureBox(ITEMTYPE type, const char* itemName, int value, int num, bool frame);		// �������� ����
	void CreateGold(ITEMTYPE type, const char* itemName, int value, int num, bool frame);				// ��� ����

	

	// ������ ���� ������
	vector<Item*>			getvItem()	{ return _vItem; }
	vector<Item*>::iterator getviItem()	{ return _viItem; }
};

