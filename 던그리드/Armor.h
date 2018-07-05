#pragma once
#include "Item.h"

struct tagArmor // �Ƹ� ����ü~~
{
	image* image[3];		//�̹��� 0. ��� 1. �κ� 2. ����
	RECT rc[3];				//��Ʈ
	ITEMTYPE type;			//������ Ÿ��
	ITEMGRADE grade;		//�����۵��
	const char* imageName;  //�̹����� �̸�(�������̸�)
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

class Armor :	public Item
{
private:
	tagArmor _armor;
	const char* _armorName;
	int _value;
public:
	Armor();
	~Armor();



	HRESULT init(ITEMTYPE type, const char* armorName, int value, POINT position);
	void release();
	void update();
	void CreateArmor(ITEMTYPE type, const char* ArmorName, int value);
	void setArmor(const char* ArmorName, int value);
	void render();

};

