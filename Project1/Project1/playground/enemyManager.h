#pragma once
#include "gameNode.h"
#include "minion.h"
#include "bullets.h"
#include <vector>

//Ŭ���� ���漱�� (��ȣ������ ����)(������ �ӵ��� ���̱� ����)
class spaceShip;

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*>				vEnemy;
	typedef vector<enemy*>::iterator	viEnemy;

private:
	vEnemy	_vMinion;	//�� ��Ƽ� ������ ����
	viEnemy _viMinion;	//����ģ�� ���ͷ�����

	bullet* _bullet;

	spaceShip* _ship;
public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//�� �����Լ�
	void setMinion(void);

	void minionBulletFire();

	void removeMinion(int arrNum);

	void collision();

	

	//�� Ŭ���������Ϳ� ���� �ּ����� �־��ִ�
	void setSpaceShipMemoryAddressLink(spaceShip* ship) { _ship = ship; }

	//�̴Ͼ� ���� ������
	vector<enemy*> getVMinion() { return _vMinion; }
	vector<enemy*>::iterator getVIMinion() { return _viMinion; }
};

