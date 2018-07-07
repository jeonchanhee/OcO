#include "stdafx.h"
#include "itemManager.h"


itemManager::itemManager(){} itemManager::~itemManager(){}


HRESULT itemManager::init()
{
	CreateItem();

	return S_OK;
}


void itemManager::release()
{


}


void itemManager::update()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); _viItem++)
	{
		(*_viItem)->update();
	}

	for (_viWeapon = _vWeapon.begin(); _viWeapon != _vWeapon.end(); _viWeapon++)
	{
		(*_viWeapon)->update();
	}

	for (_viSecond = _vSecond.begin(); _viSecond != _vSecond.end(); _viSecond++)
	{
		(*_viSecond)->update();
	}

}


void itemManager::render()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); _viItem++)
	{
		(*_viItem)->render();
	}

	for (_viWeapon = _vWeapon.begin(); _viWeapon != _vWeapon.end(); _viWeapon++)
	{
		(*_viWeapon)->render();
	}

	for (_viArmor = _vArmor.begin(); _viArmor != _vArmor.end(); _viArmor++)
	{
		(*_viArmor)->render();
	}

	for (_viAccessory = _vAccessory.begin(); _viAccessory != _vAccessory.end(); _viAccessory++)
	{
		(*_viAccessory)->render();
	}

	for (_viSecond = _vSecond.begin(); _viSecond != _vSecond.end(); _viSecond++)
	{
		(*_viSecond)->render();
	}




}

void itemManager::CreateItem()
{

	for (int i = 1; i < 6; i++)
	{
		Weapon* weapon;
		weapon = new Weapon;
		weapon->init(SWORD, "검", i, PointMake(100 + i * 200, 100));
		_vWeapon.push_back(weapon);
		_vItem.push_back(weapon);
	}

	for (int i = 1; i < 5; i++)
	{
		Weapon* weapon;
		weapon = new Weapon;
		weapon->init(GUN, "총", i, PointMake(100 + i * 200, 200));
		_vWeapon.push_back(weapon);
		_vItem.push_back(weapon);

		Armor* armor;
		armor = new Armor;
		armor->init(ARMOR, "아머", i, PointMake(100 + i * 200, 50));
		_vArmor.push_back(armor);
		_vItem.push_back(armor);

		Accessory* accessory;
		accessory = new Accessory;
		accessory->init(ACCESSORY, "악세", i, PointMake(100 + i * 200, 400));
		_vAccessory.push_back(accessory);
		_vItem.push_back(accessory);


		SecondEquipment * second;
		second = new SecondEquipment;
		second->init(SECOND_EQUIPMENT, "보조", i, PointMake(100 + i * 200, 500));
		_vSecond.push_back(second);
		_vItem.push_back(second);

	}
	
	for (int i = 1; i < 4; i++)
	{
		Weapon* weapon;
		weapon = new Weapon;
		weapon->init(BOW, "활", i, PointMake(100 + i * 200, 300));

		_vWeapon.push_back(weapon);
		_vItem.push_back(weapon);
	}


	for (int i = 1; i < 3; i++)
	{
		Weapon* weapon;
		weapon = new Weapon;
		weapon->init(HAMMER, "해머", i, PointMake(100 + i * 200, 600));
		_vWeapon.push_back(weapon);
		_vItem.push_back(weapon);

		Shield* shield;
		shield = new Shield;
		shield->init(SHIELD, "방패", i, PointMake(100 + i * 200, 700));
		_vShield.push_back(shield);
		_vItem.push_back(shield);

	}

	//for (int i = 1; i < 13; i++)
	//{
	//	Food* food;
	//	food = new Food;
	//	food->init(FOOD, "음식", i, PointMake(100 + i * 200, 600));
	//	_vFood.push_back(food);
	//	_vItem.push_back(food);
	//}

}


