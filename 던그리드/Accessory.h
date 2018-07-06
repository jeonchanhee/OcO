#pragma once
#include "Item.h"

struct tagAccessory // �Ǽ����� ����ü
{
	image* image[3];		// 0��� 1 �κ�
	ITEMTYPE type;			//�����۹���Ÿ��??
	ITEMGRADE grade;		//������ ���
	RECT rc[3];				//��Ʈ
	const char* imageName;  //�̹����� �̸�(�������̸�)
	float x, y;				//x, y ��ǥ
	int ad;					//���ݷ�
	int def;				//����	
	float attackSpeed;		//���ݼӵ�
	float moveMentSpeed;	//�̵��ӵ�	
	float criticalPersent;	//ũ��Ƽ��Ȯ��
	float evasionPersent;	//ȸ����
	int addMaxHp;			//�ִ� HP ����
	int price;				//���� ?? �������� �춧 3õ���̶���ϸ� �ȶ��� X 0.2 �ؼ� 600 �̷������� ����å��
};

class Accessory : public Item
{
private:
	tagAccessory _accessory;

	const char* _AccessoryName;
	int _value;

public:
	Accessory();
	~Accessory();

	HRESULT init(ITEMTYPE type, const char* AccessoryName, int value, POINT position);
	void release();
	void update();
	void CreateAccessory(ITEMTYPE type, const char* AccessoryName, int value);
	void setAccessory(const char* AccessoryName, int value);

	void render();
};


