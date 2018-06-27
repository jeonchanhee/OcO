#pragma once
#include "gameNode.h"
class townSene :	public gameNode
{
public:

	HRESULT init();
	void release();
	void update();
	void render();

	townSene();
	~townSene();
};

