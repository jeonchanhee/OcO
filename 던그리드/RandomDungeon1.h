#pragma once
#include "gameNode.h"
#include "dungeon1Scene.h"
#include "dungeon2Scene.h"
#include "dungeon3Scene.h"
#include "dungeon4Scene.h"
#include "dungeon5Scene.h"
#include "dungeon6Scene.h"
#include "dungeon7Scene.h"
#include "dungeon8Scene.h"
#include "weaponScene.h"
#include "foodScene.h"
#include "bossScene.h"

class RandomDungeon1 : public gameNode
{
private:
	dungeonScene* _dungeonScene;

public:
	RandomDungeon1();
	~RandomDungeon1();

	HRESULT init();
	void update();
	void render();
	void release();
	void keyControl();

	void save();
};

