#pragma once
#include "Enemy.h"


#define ARROWSPEED 10.0f

struct tagArrow
{
	image* img; 
	RECT rc;
	float x, y;
};

class Player; //�÷��̾� Ŭ���� ���漱��

class Arrow : public Enemy
{
private:
	Player * _player;

	tagArrow _arrow[3]; //0Ȱ����.1Ȱ.2ȭ��
	bool _isShoot;
	POINT _bowCenter;//Ȱ �߾�

	int	_index;
	float _arrowX, _arrowY;
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

	void playerCollision(); //�÷��̾�� Ȱ������ �浹 �Լ�
	void hitDamage(float damage);//hp���̰� �ϴ� �Լ�

	RECT  getArrowRect() { return _arrow[0].rc; } //rc

	void setPlayerAddressLink(Player* player) { _player = player; }
};