#pragma once
#include "dungeonScene.h"
#include "WeaponNpc.h"

class weaponScene :	public dungeonScene
{
private:
	WeaponNpc* _weaponNpc;

public:
	weaponScene();
	~weaponScene();
	HRESULT init();
	void setRandMapNum();
	void doorInit();
	void update();
	void render();
};

