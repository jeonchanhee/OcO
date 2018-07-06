#pragma once
#include "dungeonScene.h"
class weaponScene :
	public dungeonScene
{
public:
	weaponScene();
	~weaponScene();
	HRESULT init();
	void update();
};

