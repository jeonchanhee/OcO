#include "stdafx.h"
#include "itemManager.h"


itemManager::itemManager()
{
}


itemManager::~itemManager()
{
}


HRESULT itemManager::init()
{
	Item* item;
	item = new Item;
	//item->createItem("무기", SECOND_EQUIPMENT, 4, true);
	_vItem.push_back(item);
	



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

void itemManager::CreateWeapon(bool frame)
{
	/*for (int i = 1; i < 6; i++)
	{

		if (item->getimageType() == 단일)
		{
			item->createItem(SHORT_DISTANCE_WEAPON, 단일,  )
			_vItem.push_back(item);
		}
	}*/
}

//void itemManager::CreateDefenceMechanism(ITEMTYPE type, const char* itemName, int value, int num, bool frame)
//{
//
//	item->createItem(type, itemName, value, num, frame);
//	_vItem.push_back(item);
//}
//
//
//void itemManager::CreateSecondEquipment(ITEMTYPE type, const char* itemName, int value, int num, bool frame)
//{
//
//	item->createItem(type, itemName, value, num, frame);
//	_vItem.push_back(item);
//}
//
//
//void itemManager::CreateAccessory(ITEMTYPE type, const char* itemName, int value, int num, bool frame)
//{
//
//	item->createItem(type, itemName, value, num, frame);
//	_vItem.push_back(item);
//}
//
//
//void itemManager::CreateFood(ITEMTYPE type, const char* itemName, int value, int num, bool frame)
//{
//
//	item->createItem(type, itemName, value, num, frame);
//	_vItem.push_back(item);
//}
//
//
//void itemManager::CreateTreasureBox(ITEMTYPE type, const char* itemName, int value, int num, bool frame)
//{
//
//	item->createItem(type, itemName, value, num, frame);
//	_vItem.push_back(item);
//}
//
//
//void itemManager::CreateGold(ITEMTYPE type, const char* itemName, int value, int num, bool frame)
//{
//	item->createItem(type, itemName, value, num, frame);
//	_vItem.push_back(item);
//}
