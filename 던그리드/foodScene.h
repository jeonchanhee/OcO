#pragma once
#include "dungeonScene.h"
#include "FoodNpc.h"

class foodScene : public dungeonScene
{
private:
	FoodNpc* _foodNpc;
public:
	foodScene();
	~foodScene();
	HRESULT init();
	void update();
	void setRandMapNum();
	void doorInit();
	void render();
};

