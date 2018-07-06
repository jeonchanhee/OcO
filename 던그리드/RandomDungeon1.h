#pragma once
#include "gameNode.h"
#include "dungeon1Scene.h"
#include "dungeon2Scene.h"
#include "dungeon3Scene.h"
#include "dungeon4Scene.h"
#include "dungeon7Scene.h"
#include "dungeon8Scene.h"

class RandomDungeon1 : public gameNode
{
	bool _isClearScene[6];
	RECT _rc;
public:
	RandomDungeon1();
	~RandomDungeon1();
};

