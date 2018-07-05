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
