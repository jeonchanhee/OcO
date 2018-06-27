#pragma once
#include "gameNode.h"
class enemeyManager :	public gameNode
{
public:

	HRESULT init();
	void release();
	void update();
	void render();

	enemeyManager();
	~enemeyManager();
};

