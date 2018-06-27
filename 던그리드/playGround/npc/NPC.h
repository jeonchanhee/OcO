#pragma once
#include "gameNode.h"
class NPC :	public gameNode
{
public:

	HRESULT init();
	void release();
	void update();
	void render();

	NPC();
	~NPC();
};

