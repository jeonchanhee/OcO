#pragma once
#include "gameNode.h"
class Player :	public gameNode
{
public:

	HRESULT init();
	void release();
	void update();
	void render();

	Player();
	~Player();
};

