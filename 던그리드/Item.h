#pragma once
#include "gameNode.h"


enum ITEMTYPE // �������� Ÿ��
{
	SHORT_ATTACK,	// ��������
	LONG_ATTACK,	// ���Ÿ� ����
	SECOND_EQUIPMENT, // ������� 
	ACCESSORY,		// �׼�����
	FOOD,			// ����
	HEALING,		// ����
	TREASUREBOX,	// �����ڽ�
	GOLD			// ���� / ����
};


struct tagItem
{
	image* image[3];		//�̹��� 0�迭 : �������� 1 : �迭 �κ��丮�������� 2�迭 :������������  (�̰͸��������ִ��� bool�ش�)
	ITEMTYPE type;			//d�����۹���Ÿ��??
	RECT rc;				// ��Ʈ
	bool isFrame;			//bool �� �������ΰ� ??
	int ad;					//���ݷ�
	int armor;				//����	
	int attackSpeed;		//���ݼӵ�
	float moveMentSpeed;	//�̵��ӵ�	
	float criticalPersent;	//ũ��Ƽ��Ȯ��
	float dashPower;		//��ð��ݷ� ������ 
	int addMaxHp;			//�ִ� HP ����
	int fullNess;			//������ ������� ? food�϶��� ����??
	int evasionPersent;		//ȸ���� 
	int fixedDamage;		//������ 
	int price;				//���� ?? �������� �춧 3õ���̶���ϸ� �ȶ��� X 0.2 �ؼ� 600 �̷������� ����å��
};


class Item : public gameNode
{
private:

	vector<tagItem>				_vItem;
	vector<tagItem>::iterator	_viItem;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	void createItem(int value , ITEMTYPE type , bool frame);
	



	vector<tagItem>				getvItem()		{ return _vItem; }
	vector<tagItem>::iterator	getviItem()		{ return _viItem; }
};
