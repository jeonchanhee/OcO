#pragma once
#include "gameNode.h"
class minimap : public gameNode
{
private:
	image* _minimap;

public:
	minimap();
	~minimap();

	HRESULT init();
	void release();
	void render();
	void update();
	void setMinimap(HDC dc);
};

