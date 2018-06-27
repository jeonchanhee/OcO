#pragma once
#include "gameNode.h"

class Item :	public gameNode
{
public:

	HRESULT init();
	void release();
	void update();
	void render();

	Item();
	~Item();
};

