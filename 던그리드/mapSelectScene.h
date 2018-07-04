#pragma once
#include "gameNode.h"
class mapSelectScene : public gameNode
{
private:
	string _mapName;

public:
	mapSelectScene();
	~mapSelectScene();

	HRESULT init();
	void update();
	void release();
	void render();

	void load();
	void printMap();
	void chooseMap(int idx);
};

