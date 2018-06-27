#pragma once
#include "gameNode.h"


class MapTool :	public gameNode
{
public:

	HRESULT init();
	void release();
	void update();
	void render();

	MapTool();
	~MapTool();
};

