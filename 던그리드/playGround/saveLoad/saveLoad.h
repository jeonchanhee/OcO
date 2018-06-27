#pragma once
#include "gameNode.h"
class saveLoad :public gameNode
{
public:

	HRESULT init();
	void release();
	void update();
	void render();

	saveLoad();
	~saveLoad();
};

