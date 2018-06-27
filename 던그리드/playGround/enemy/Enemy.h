#pragma once
#include "gameNode.h"
class Enemy :	public gameNode
{
public:

	HRESULT init();
	void release();
	void update();
	void render();

	Enemy();
	~Enemy();
};

