#pragma once
#include "gameNode.h"
class rewardDieScene :	public gameNode
{
public:

	HRESULT init();
	void release();
	void update();
	void render();

	rewardDieScene();
	~rewardDieScene();
};

