#pragma once
#include "gameNode.h"

class Player;

class townScene : public gameNode
{
private:
	Player* _player;
	string	_mapName;
	image* _pixel;
	image* _trainer;
	image* _shop;
	animation* _training;
	animation* _shopping;
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

