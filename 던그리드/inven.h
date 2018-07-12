#pragma once
#include "gameNode.h"
#include "item.h"
class inven : public gameNode
{
private:
	//�κ��丮 
	vector<Item*> _vItem;
	vector<Item*>::iterator _viItem;
	//�ֹ���
	vector<Item*> _vMainWeapon;
	//��������
	vector<Item*> _vAssistWeapon;
	//Accessarry
	vector<Item*> _vAccessary;

	//inven 
	image * _image[15];
	RECT _selectRect[15];
	RECT _mainWeaponRect[2];
	RECT _assistWeaponRect[2];
	RECT _accessarryRect[4];
	bool _onMouseInven, _onMouseAc , _onMouseMain , _onMouseAs , _onInven;
	int _isSelect;
	long _halfW, _halfH;
	short _index, _index2;

public:


	HRESULT init();
	void release();
	void update();
	void render();

	//���� ���� ȹ�� ���� 
	void setIsSelect(int index) { _isSelect = index; }
	int getIsSelect()			{ return _isSelect; }

	vector<Item*> getItem()			{ return _vItem; }
	vector<Item*> getMainWeapon()   { return _vMainWeapon; }
	vector<Item*> getAssistWeapon() { return _vAssistWeapon; }
	vector<Item*> getAccessarry()   { return _vAccessary; }
	
	void dismantItem();
	void mount();
	void pickUpItem(ITEMTYPE type, const char * weaponName, int value);
	void deleteItem(int i);

	
	inven();
	~inven();
};

