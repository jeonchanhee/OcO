#pragma once
#include "dungeonScene.h"

class dungeon2Scene : public dungeonScene
{
private:
	image * _pixel;
public:
	dungeon2Scene();
	~dungeon2Scene();

	HRESULT init();
	void setRandMapNum();
	void doorInit();

	void update();

	void setMonster();

	image* getPixel() { return _pixel; }
};

