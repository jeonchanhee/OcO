#pragma once
#include "gameNode.h"
#include "minimap.h"
#include "RandomDungeon1.h"

class Player;
class itemManager;

class townScene : public gameNode
{
private:
	itemManager * _im;
	Player* _player;
	string	_mapName;
	image* _pixel;
	image* _trainer;
	image* _shop;
	image* _suckImg;
	animation* _training;
	animation* _shopping;
	animation* _suck;
	int		_temp;
	int _start;
	bool _ui[3];
	bool _sucking;

	minimap* _minimap;
	RandomDungeon1* _randMap;
	
public:
	void setImLink(itemManager* im) { _im = im; }

	HRESULT init();
	void release();
	void update();
	void render();
	void mapload();
	void setMinimap();
	void mapRender();
	void NPC();
	void training();
	void shop();
	void dungeonGo();
	static	void suckDungeon(void * object);
	static void moveDungeon(void * object);
	townScene();
	~townScene();
};

