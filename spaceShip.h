#pragma once
#include "gameNode.h"
#include "bullets.h"
#include "progressBar.h"

//�̰� �ּ��Դϱ�? �ּ��̿���?! 
#pragma warning(disable:4996)

//��ȣ������ ���� ���漱�� (���� �ӵ��� �� �� _��)b )
class enemyManager;

class spaceShip : public gameNode
{
private:
	image* _ship;		//���ּ� �̹��� 
	missile* _missile;	//�̻��� Ŭ����
	minho* _hoooo;

	enemyManager* _em;

	progressBar* _hpBar;		//�����̽� �� HP��
	float _currentHP, _maxHP;	//����ü�� / �ִ�ü��

	int _alphaValue;

public:
	spaceShip();
	~spaceShip();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void collision();

	//�ǰ� �� HP ����ִ� �Լ�
	void hitDamage(float damage);

	image* getShipImage() { return _ship; }

	void setEmMemoryAddressLink(enemyManager* em) { _em = em; }

	minho* getMinho() { return _hoooo; }

};

