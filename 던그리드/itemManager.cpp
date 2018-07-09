#include "stdafx.h"
#include "itemManager.h"


itemManager::itemManager(){} itemManager::~itemManager(){}


HRESULT itemManager::init()
{
	//CreateItem();

	_foodNpc = new FoodNpc;
	_foodNpc->init(NPC_LEFT_STOP, FOOD_NPC, "엔피시", 1, PointMake(200, 200));

	_weaponNpc = new WeaponNpc;
	_weaponNpc->init(NPC_LEFT_STOP, WEAPON_NPC, "엔피시", 2, PointMake(400, 100));
	


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

	_weaponNpc->update();
	_foodNpc->update();
}


void itemManager::render()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); _viItem++)
	{
		(*_viItem)->render();
	}
	_weaponNpc->render();
	_foodNpc->render();
}

void itemManager::CreateItem()
{

	for (int i = 1; i < 6; i++)
	{
		Item* weapon;
		weapon = new Weapon;
		weapon->init(SWORD, "검", i, PointMake(100 + i * 300, 100));
		_vItem.push_back(weapon);
	}

	for (int i = 1; i < 5; i++)
	{
		Item* weapon;
		weapon = new Weapon;
		weapon->init(GUN, "총", i, PointMake(100 + i * 300, 200));
		_vItem.push_back(weapon);
		
		Item* armor;
		armor = new Armor;
		armor->init(ARMOR, "아머", i, PointMake(100 + i * 300, 500));
		_vItem.push_back(armor);

		Item* accessory;
		accessory = new Accessory;
		accessory->init(ACCESSORY, "악세", i, PointMake(100 + i * 300, 700));
		_vItem.push_back(accessory);

		Item* second;
		second = new SecondEquipment;
		second->init(SECOND_EQUIPMENT, "보조", i, PointMake(100 + i * 300, 800));
		_vItem.push_back(second);

	}
	
	for (int i = 1; i < 4; i++)
	{

		Item* weapon;
		weapon = new Weapon;
		weapon->init(BOW, "활", i, PointMake(100 + i * 300, 300));
		_vItem.push_back(weapon);
	}


	for (int i = 1; i < 3; i++)
	{
		Item* weapon;
		weapon = new Weapon;
		weapon->init(HAMMER, "해머", i, PointMake(100 + i * 300, 400));
		_vItem.push_back(weapon);

		Item* shield;
		shield = new Shield;
		shield->init(SHIELD, "방패", i, PointMake(100 + i * 300, 600));
		_vItem.push_back(shield);
	}

	for (int i = 1; i < 5; i++)
	{
		Item* food;
		food = new Food;
		food->init(FOOD, "음식", i, PointMake(100 + i * 200, 900));
		_vItem.push_back(food);
	}

}


