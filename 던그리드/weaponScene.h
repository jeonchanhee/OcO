#pragma once
#include "dungeonScene.h"
#include "WeaponNpc.h"


class townScene;

class weaponScene :	public dungeonScene
{
private:
	townScene* _tc;
	WeaponNpc* _weaponNpc;

public:
	void setTcLink(townScene* tc) { _tc = tc; }

	weaponScene();
	~weaponScene();
	HRESULT init();
	void setRandMapNum();
	void doorInit();
	void update();
	void render();
};

