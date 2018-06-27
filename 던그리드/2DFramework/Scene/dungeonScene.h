#pragma once
#include "gameNode.h"
class dungeonScene :public gameNode
{
public:

	HRESULT init();
	void release();
	void update();
	void render();

	dungeonScene();
	~dungeonScene();
};

