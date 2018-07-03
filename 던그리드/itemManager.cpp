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
	/*Item* item;
	item = new Item;
	item->createItem("°Ë", SHORT_DISTANCE_WEAPON, 5, true);
	_vItem.push_back(item);
	*/

	return S_OK;
}


void itemManager::release()
{


}


void itemManager::update()
{
	/*for (_viItem = _vItem.begin(); _viItem != _vItem.end(); _viItem++)
	{
		(*_viItem)->update();
	}*/
}


void itemManager::render()
{
	/*for (_viItem = _vItem.begin(); _viItem != _vItem.end(); _viItem++)
	{
		(*_viItem)->render();
	}*/
}
