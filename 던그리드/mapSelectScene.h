#pragma once
#include "gameNode.h"
class mapSelectScene : public gameNode
{
private:
	string _mapName;
	int _mapIdx;

public:
	mapSelectScene();
	~mapSelectScene();

	HRESULT init();
	void update();
	void release();
	void render();

	void load();
	void printMap(int idx);
	void chooseMap(int idx);

	void setCamera(void);
};
