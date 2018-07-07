#pragma once
#include "dungeonScene.h"
class foodScene :
	public dungeonScene
{
public:
	foodScene();
	~foodScene();
	HRESULT init();
	void update();
};

