#pragma once
#include "gameNode.h"

class Item :	public gameNode
{
private:
	image*	_image; // ������ �̹���
	RECT	_rc; // ������ ��Ʈ
	float	_x, _y; // ������ x, y��ǥ
	

public:

	Item();
	~Item();

	HRESULT init();
	void release();
	void update();
	void render();

};

