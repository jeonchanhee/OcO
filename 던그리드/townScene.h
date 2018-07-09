#pragma once
#include "gameNode.h"
class townScene : public gameNode
{
public:
	HRESULT init();
	void release();
	void update();
	void render();
	townScene();
	~townScene();
};

