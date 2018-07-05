#pragma once
#include "Item.h"


struct tagSecondEquipment // ������� ����ü~~
{
	image* image[3];		//�̹��� 0. ��� 1. �κ� 2. ����
	RECT rc[3];				//��Ʈ
	ITEMTYPE type;			//������ Ÿ��
	ITEMGRADE grade;		//������ ���
	int frameX, frameY;		// ������ X, Y
	bool isFrame;			// �������̹��� Ȯ�ο�
	float x, y;				//x, y ��ǥ
	int ad;					// ���ݷ�
	int def;				//����	
	float attackSpeed;		//���ݼӵ�
	float moveMentSpeed;	//�̵��ӵ�	
	float criticalPersent;	//ũ��Ƽ��Ȯ��
	float evasionPersent;	//ȸ����
	int addMaxHp;			//�ִ� HP ����
	int price;				//���� ?? �������� �춧 3õ���̶���ϸ� �ȶ��� X 0.2 �ؼ� 600 �̷������� ����å��
};


class SecondEquipment : public Item
{
private:

	tagSecondEquipment _second;

	int _count;
public:

	SecondEquipment();
	~SecondEquipment();

	HRESULT init();
	void release();
	void update();
	void render();


	void CreateEquipment(ITEMTYPE type, const char* secondEquipmentName, int value, POINT position);
	void setEquip(const char* secondEquipment, int value);
};

