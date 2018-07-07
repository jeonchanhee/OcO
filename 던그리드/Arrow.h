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
	tagArrow _arrow[3]; //0Ȱ����.1Ȱ.2ȭ��
	bool _isShoot;
	POINT _bowCenter;//Ȱ �߾�

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
	void fireArrow(); //Ȱ���̰� ���콺�������� Ȱ��� �ϴ� ����
};