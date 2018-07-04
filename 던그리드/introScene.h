#pragma once
#include "gameNode.h"
class introScene : public gameNode
{
public:
	introScene();
	~introScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

