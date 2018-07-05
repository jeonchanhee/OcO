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


}


void itemManager::render()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); _viItem++)
	{
		(*_viItem)->render();
	}

}

void itemManager::CreateItem()
{
	
	for (int i = 1; i < 6; i++)
	{
		Weapon* weapon;
		weapon = new Weapon;
		weapon->init(SWORD, "검", i, PointMake(200 + i * 100, 200));
		_vWeapon.push_back(weapon);
		_vItem.push_back(weapon);
	}

	for (int i = 1; i < 5; i++)
	{
		Armor* armor;
		armor = new Armor;
		armor->init(ARMOR, "아머", i, PointMake(600 + i * 100, 200));
		_vArmor.push_back(armor);
		_vItem.push_back(armor);

	}

	//for (int i = 1; i < 3; i++)
	//{
	//	Shield* shield;
	//	shield = new Shield;
	//	shield->init(SHIELD, "방패", i, PointMake(500, 200));
	//	_vShield.push_back(shield);
	//	_vItem.push_back(shield);
	//}

}


