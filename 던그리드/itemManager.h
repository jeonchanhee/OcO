#pragma once
#include "Item.h"
#include "gameNode.h"

class itemManager : public gameNode
{
private:
	typedef vector <Item*> Vitem;
	typedef vector <Item*>::iterator VIitem;

	Item inven[23];

private:
	Vitem _vItem;
	VIitem _viItem;
public:
	itemManager();
	~itemManager();

	vector <Item*> getItem() { return _vItem; }

	HRESULT init();
	void release();
	void update();
	void render();
};

