#pragma once
#include "Item.h"


struct tagShield // ���� ����ü~~
{
	image* image[3];		//�̹��� 0. ��� 1. �κ� 2. ����
	RECT rc[3];				//��Ʈ
	ITEMTYPE type;			//������ Ÿ��
	ITEMGRADE grade;		//������ ���
	const char* imageName;  //�̹����� �̸�(�������̸�)
	float x, y;				//x, y ��ǥ
	int ad;					//���ݷ�
	int def;				//����	
	float attackSpeed;		//���ݼӵ�
	float moveMentSpeed;	//�̵��ӵ�
	float dashPower;		//��ð��ݷ� ������
	float criticalPersent;	//ũ��Ƽ��Ȯ��
	float evasionPersent;	//ȸ����
	int addMaxHp;			//�ִ� HP ����
	int price;				//���� ?? �������� �춧 3õ���̶���ϸ� �ȶ��� X 0.2 �ؼ� 600 �̷������� ����å��
};


class Shield : public Item
{
private:
	tagShield _shield;

	const char* _ShieldName;
	int _value;
public:
	Shield();
	~Shield();

	HRESULT init(ITEMTYPE type, const char* ShieldName, int value, POINT position);
	void release();
	void update();

	void CreateShield(ITEMTYPE type, const char* ShieldName, int value);
	void setShield(const char* ShieldName, int value);
	void render();

};

