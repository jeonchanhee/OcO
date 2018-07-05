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
	typedef vector <Item*>							vItem; // ��ü ������ ������������� �κ��丮 �ȿ� �ִ� ����������, �����ϰ� �ִ��� Ȯ�ο� ��
	typedef vector <Item*>::iterator				viItem;

	typedef vector <Weapon*>						vWeapon; // ������ü�� ���� ����
	typedef vector <Weapon*>::iterator				viWeapon;

	typedef vector <Armor*>							vArmor; // �Ƹ� ��ü�� ���� ����
	typedef vector <Armor*>::iterator				viArmor;

	typedef vector <Shield*>						vShield; // ���� ��ü�� ���� ����
	typedef vector <Shield*>::iterator				viShield;

	typedef vector <SecondEquipment*>				vSecond; // ������� ��ü�� ���� ����
	typedef vector <SecondEquipment*>::iterator		viSecond;

	typedef vector <Accessory*>						vAccessory; //  �Ǽ����� ��ü�� ���� ����
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

	void CreateItem();																						// ���� ����

	// ������ ���� ������

	vector<Item*>			getvItem()	{ return _vItem; }
	vector<Item*>::iterator getviItem()	{ return _viItem; }
};

