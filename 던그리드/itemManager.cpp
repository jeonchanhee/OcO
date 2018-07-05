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
	putItem();

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

void itemManager::putItem()
{
	Item* item;
	item = new Item;
	
	for (int i = 0; i < 3; i++)
	{
		item->createItem("��", SHORT_DISTANCE_WEAPON, 1, true);
	}

	for (int i = 0; i < 4; i++)
	{
		item->createItem("��", LONG_DISTANCE_WEAPON, 2, true);
	}

	for (int i = 0; i < 5; i++)
	{
		item->createItem("��", DEFENCE_MECHANISM, 3, true);
	}

	for (int i = 0; i < 5; i++)
	{
		item->createItem("��", SECOND_EQUIPMENT, i, true);
	}

	for (int i = 0; i < 5; i++)
	{
		item->createItem("��", ACCESSORY, i, true);
	}

	for (int i = 0; i < 5; i++)
	{
		item->createItem("��", GOLD, i, true);
	}

	_vItem.push_back(item);

}
