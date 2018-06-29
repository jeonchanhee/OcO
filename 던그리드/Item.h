#pragma once
#include "gameNode.h"

class Item :	public gameNode
{
private:
	image*	_image; // 아이템 이미지
	RECT	_rc; // 아이템 렉트
	float	_x, _y; // 아이템 x, y좌표
	

public:

	Item();
	~Item();

	HRESULT init();
	void release();
	void update();
	void render();

};

