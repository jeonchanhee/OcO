#pragma once
#include "Enemy.h"
#define ARROWSPEED 10.0f

struct tagArrow
{
	image* img; 
	RECT rc;
	float x, y;
};

class Arrow : public Enemy
{
private:
	tagArrow _arrow[3]; //0활쟁이.1활.2화살
	bool _isShoot;
	POINT _bowCenter;//활 중앙

	int	_index;

public:
	Arrow();
	~Arrow();

	HRESULT init(float x, float y);
	void release();
	void update();
	void render();

	void frameMove();
	void shootArrow();
	void fireArrow(); //활쟁이가 마우스방향으로 활쏘게 하는 내용
};