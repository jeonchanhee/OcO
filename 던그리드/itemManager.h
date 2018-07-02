#pragma once
#include "Item.h"
class itemManager
{
private:
	typedef vector <item*> Vitem;
	typedef vector <item*>::iterator VIitem;
private:
	Vitem _vItem;
	VIitem _viItem;
public:
	itemManager();
	~itemManager();
};

