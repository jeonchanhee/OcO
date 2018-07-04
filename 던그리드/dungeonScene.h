#pragma once
#include "gameNode.h"

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
	torch	_torch;		// ȶ��
	Door	_door;		// ��
	Portal	_portal;	// ��Ż

	int dungeonNum;
	int tileSize[11] = {}

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void mapload();
	


	dungeonScene();
	~dungeonScene();
};

