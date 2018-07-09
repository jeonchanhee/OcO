#pragma once
#include "gameNode.h"

class Player;

class townScene : public gameNode
{
private:
	Player* _player;
	string	_mapName;
	int		_temp;

public:
	HRESULT init();
	void release();
	void update();
	void render();
	void mapload();
	void mapRender();
	townScene();
	~townScene();
};

