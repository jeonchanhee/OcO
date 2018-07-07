#pragma once
#include "gameNode.h"


enum ITEMGRADE //������ ���
{
	NORMAL,		// �븻
	RARE,		// ���� 
	LEGENDARY	// ����
};

enum ITEMTYPE // �������� Ÿ��
{
	WEAPON,						// ����
	SWORD, HAMMER, GUN, BOW,	// ��, �ظ� ,�� , Ȱ
	ARMOR,						// �Ƹ�
	SHIELD,						// ����
	SECOND_EQUIPMENT,			// ������� 
	ACCESSORY,					// �׼�����
	FOOD,						// ����
	GOLD,						// ���� / ����
};

enum ITEMCONDITION
{
	DROPITEM,	// ������������� 
	INVENITEM,	// �κ��丮 �ȿ� �ִ� ������ ����.
	WEARITEM,	// �������������
};

struct tagItem // ������
{
	image* image[13];			// 0.��� 1.�κ� 2. ����
	RECT rc[13];					// ��Ʈ
	ITEMTYPE type;				// ������ ����
	ITEMGRADE grade;			// ������ ���
	float x, y;					//x, y ��ǥ
	bool isFrame;				// ������ �̹��� ���� �ƴ��� Ȯ��
	bool sellBan;				// �Ǹű��� ������ ���� �ƴ���
	int frameX, frameY;			//������ X, Y
	int minimumAtt, MaxAtt;		//�ּ� ~ �ִ� ���ݷ� 20 ~ 30 �̸� �������� 22����?
	int ad;						//���ݷ�
	int fixedDamage;			//������ 22;
	float attackSpeed;			//���ݼӵ�	
	float moveMentSpeed;		//�̵��ӵ�
	float criticalPersent;		//ũ��Ƽ��Ȯ��
	float evasionPersent;		//ȸ����
	float hpRecovery;			//hpȸ��
	float dashPower;			//��ð��ݷ� ������ 
	int addMaxHp;				//�ִ� HP ����
	int price;					//���� ?? �������� �춧 3õ���̶���ϸ� �ȶ��� X 0.2 �ؼ� 600 �̷������� ����å��
};


class Item : public gameNode
{
private:
	ITEMCONDITION _condition;
	bool _isDropItem; // ������������� �ƴ��� Ȯ��
	bool _isInvenItem; // �κ��丮�� �����ϰ� �ִ� ������ ���� �ƴ��� Ȯ��
	bool _isWearItem; // ȭ�� �ȿ��� ������ �����ϰ� �ִ� �̹��� ���� �ƴ��� Ȯ��
	
	
public:
	Item();
	~Item();

	HRESULT init();
	void release();
	void update();
	void render();

	void ItemDirection();

	void setDropItem();
	void setInvenItem();
	void setWearItem();


	



};
