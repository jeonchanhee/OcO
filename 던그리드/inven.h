#pragma once
#include "gameNode.h"
#include "item.h"

#define INVENSIZE 15

class itemManager;

class inven : public gameNode
{
private:
	itemManager * _im;
	//�κ��丮 
	vector<Item*> _vItem;
	vector<Item*>::iterator _viItem;
	//�ֹ���
	vector<Item*> _vMainWeapon;
	//��������
	vector<Item*> _vAssistWeapon;
	//Accessarry
	vector<Item*> _vAccessary;
	//save vector 
	vector<Item*> _vSaveItem;

	//inven 
	image * _image[15];
	RECT _selectRect[15];
	RECT _mainWeaponRect[2];
	RECT _assistWeaponRect[2];
	RECT _accessarryRect[4];
	RECT _moneyRect;
	bool _onMouseInven, _onMouseAc , _onMouseMain , _onMouseAs , _onInven;
	int _isSelect;
	int _gold;
	long _halfW, _halfH;
	short _index, _index2;

public:


	HRESULT init();
	void release();
	void update();
	void render();

	void setImLink(itemManager* im) { _im = im; } 

	void setOnInven(int on) { _onInven = on; }
	void setIsSelect(int index) { _isSelect = index; }
	int getIsSelect()			{ return _isSelect; }

	vector<Item*> getItem()			{ return _vItem; }
	vector<Item*> getMainWeapon()   { return _vMainWeapon; }
	vector<Item*> getAssistWeapon() { return _vAssistWeapon; }
	vector<Item*> getAccessarry()   { return _vAccessary; }
	

	
	void mount(); //���� 
	void pickUpItem(ITEMTYPE type, const char * weaponName, int value);
	void buyItem(int num);
	// ȹ�� 
	void deleteItem(int i);  //���� 
	void dismantWeapon();
	void dismantAs();
	void dismantAccessarry();
	
	int getGold() { return _gold; }
	void setGold(int i) { _gold = i; }
	
	inven();
	~inven();
};

