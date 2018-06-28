#pragma once
#include "gameNode.h"


class UI :	public gameNode
{
public:

	HRESULT init();
	void release();
	void update();
	void render();
	
	UI();
	~UI();
};

