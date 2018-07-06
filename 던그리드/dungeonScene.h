#pragma once
#include "gameNode.h"
#include "Enemy.h"
#include "Arrow.h"
#include "BigBone.h"
#include "Bat.h"
#include "RedBat.h"
#include "DogBone.h"

struct torch
{
	image* img;
	int x, y;
};

struct Door
{
	image* img;
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

	torch	_torch;		// È¶ºÒ
	Door	_door;		// ¹®
	Portal	_portal;	// Æ÷Å»
	string _mapName;
	int _dungeonNum;
	int _temp;
	

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void mapload();

	void setCamera(void);

	void selectSize(int idx);

	void chooseMap(int idx);

	dungeonScene();
	~dungeonScene();

	void setDogBone(int idX, int idY);
	void setBigBone(int idX, int idY);
	void setArrow(int idX, int idY);
	void setBat(int idX, int idY);
	void setRedBat(int idX, int idY);
};

