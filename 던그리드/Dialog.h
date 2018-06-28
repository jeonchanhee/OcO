#pragma once
#include "gameNode.h"

class Dialog :	public gameNode
{
public:

	HRESULT init();
	void release();
	void update();
	void render();

	Dialog();
	~Dialog();
};

