#pragma once
#include "gameNode.h"


enum ITEMTYPE // �������� Ÿ��
{
	SHORT_DISTANCE_WEAPON,	// ��������
	LONG_DISTANCE_WEAPON,	// ���Ÿ� ����
	DEFENCE_MECHANISM,		// ��
	SECOND_EQUIPMENT,		// ������� 
	ACCESSORY,				// �׼�����
	CONSUME,				// �Һ�Ǵ� ��� ������(����)
	HEALING,				// ����
	TREASUREBOX,			// �����ڽ�
	GOLD					// ���� / ����
};


struct tagItem // ������ ����ü~~
{
	image* image[3];		//�̹��� 0�迭 : �������� 1 : �迭 �κ��丮�������� 2�迭 :������������  (�̰͸��������ִ��� bool�ش�)
	ITEMTYPE type;			//d�����۹���Ÿ��??
	RECT rc;				// ��Ʈ
	const char* imageName;  //�̹����� �̸�(�������̸�)
	float x, y;				//x, y ��ǥ
	bool isFrame;			//bool �� �������ΰ� ??
	int frameX, frameY;		//������ X, Y
	int ad;					//���ݷ�
	int armor;				//����	
	float attackSpeed;		//���ݼӵ�
	float moveMentSpeed;	//�̵��ӵ�	
	float criticalPersent;	//ũ��Ƽ��Ȯ��
	float evasionPersent;	//ȸ����
	float dashPower;		//��ð��ݷ� ������ 
	int addMaxHp;			//�ִ� HP ����
	int heal;				//��
	int fullNess;			//������ ������� ? food�϶��� ����??
	int fixedDamage;		//������ 
	int gold;				// ��� �������� ������ ����
	int price;				//���� ?? �������� �춧 3õ���̶���ϸ� �ȶ��� X 0.2 �ؼ� 600 �̷������� ����å��
	bool isfly;				// �����ִ�?
};


class Item : public gameNode
{
private:
	tagItem _item;
	int _count;
public:

	HRESULT init();
	void release();
	void update();
	void render();

					         //������ �̸� //������ Ÿ��  //������ ��ȣ // ������ �̹����ΰ�?
	void createItem(const char* imageName, ITEMTYPE type, int value, bool frame);
	
	void LongDistanceWeapon(const char* imageName, int value);				// ���Ÿ� ����
	void ShortDistanceWeapon(const char* imageName, int value);				// �ٰŸ� ����
	void DefenceMechanism(const char* imageName, int value);				// ��
	void SecondEquipment(const char* imageName, int value);					// �������
	void Accessory(const char* imageName, int value);						// �Ǽ��縮
	void Consume(const char* imageName, int value);							// �Һ������
	void Healing(const char* imageName, int value);							// ��������~
	void TreasureBox(const char* imageName, int value);						// �����ڽ�(���⼭ ��� / �������� ����)
	void Gold(const char* imageName, int value);							// ���� / ����
};
