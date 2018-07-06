#pragma once
#include "gameNode.h"
#include "Enemy.h"

class RandomDungeon1;

struct torch
{
	image* img;
	int x, y;
};

struct Door
{
	image* img;
	RECT rc;
	int x, y;
};

struct Portal
{
	image* img;
	int x, y;
};

class dungeonScene : public gameNode
{
protected:
	vector<Enemy*>					_vEnemy;
	vector<Enemy*>::iterator		_viEnemy;

	vector<int> _route;
	RandomDungeon1* _random;

	torch	_torch;		// È¶ºÒ
	//Door	_door;		// ¹®
	vector<Door> _door;
	Portal	_portal;	// Æ÷Å»
	string _mapName;
	int _randNum;
	int _dungeonNum;
	int _temp;
	string _mapValue[11];

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void mapload();

	void setCamera(void);

	void selectSize(int idx);

	void chooseMap(int idx);

	void nextTest();

	void load();

	void save();

	dungeonScene();
	~dungeonScene();

	void setRandomDungeonLink(RandomDungeon1* random) { _random = random; }
};

