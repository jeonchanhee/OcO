#pragma once
#include "Enemy.h"
#include "progressBar.h"

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

	progressBar* _progressBar; //ü�¹�
	float _currentHP, _maxHP; //����ü�°� �ִ�ü��


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

	int getCurrentHp() { return _currentHP; } //���� hp
	int getMaxHp() { return _maxHP; } //��ühp
	void setCurrentHp(int currentHP) { _currentHP = currentHP; }
	void setMaxHp(int maxHP) { _maxHP = maxHP; }
	RECT  getArrowRect() { return _arrow[0].rc; } //rc

	void setPlayerAddressLink(Player* player) { _player = player; }
};