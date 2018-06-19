#pragma once
#include "gameNode.h"
#include "ship.h"

class battle;

class starScene : public gameNode
{
private:
	ship* _battle;

public:
	starScene();
	~starScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

