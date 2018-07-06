#pragma once
#include "dungeonScene.h"
class bossScene :
	public dungeonScene
{
public:
	bossScene();
	~bossScene();
	HRESULT init();
};

