#pragma once
#include "gameNode.h"


enum ITEMGRADE //������ ���
{
	NORMAL,		// �븻
	RARE,		// ���� 
	LEGENDARY	// ����
};

enum PROPERTYTYPE
{
	COIN,
	GOLDBAR
};

enum ITEMTYPE // �������� Ÿ��
{
	SWORD, HAMMER, GUN, BOW,	// ��, �ظ� ,�� , Ȱ
	ARMOR,						// �Ƹ�
	SHIELD,						// ����
	SECOND_EQUIPMENT,			// ������� 
	ACCESSORY,					// �׼�����
	FOOD,						// ����

};



enum DROPITEM // ���������
{
	DR_SWORD, DR_HAMMER, DR_GUN, DR_BOW,			// ����������� �� / �ظ� / �� / Ȱ �϶�
	DR_ARMOR, DR_SHIELD, DR_SECOND, DR_ACCESSORY,	// ����������� �Ƹ� / ���� / ���� ��� / �Ǽ����� �� ��
	DR_COIN, DR_GOLDBAR								// ����������� ���� / ���� �� ��
};

enum INVENITEM // �κ��� �ִ� ������
{
	IV_SWORD, IV_HAMMER, IV_GUN, IV_BOW,			// �κ��� �ִ� �������� �� / �ظ� / �� / Ȱ �� ��
	IV_ARMOR, IV_SHIELD, IV_SECOND, IV_ACCESSORY,	// �κ��� �ִ� �������� �Ƹ� / ���� / ���� ��� / �Ǽ����� �� ��
	IV_COIN											// �κ��� �ִ� �������� ������ ��
};

enum WEARITEM
{
	WR_SWORD, WR_HAMMER, WR_GUN, WR_BOW,			// ������ �������� �� / �ظ� / �� / Ȱ �� ��
	WR_SECOND										// ������ �������� ���� ��� �� ��
};

struct tagproperty
{
	image* image;		// �̹���
	RECT rc;			// ��Ʈ
	PROPERTYTYPE type;	// �����̳� ���ٳ�
	float x, y;			// x, y ��ǥ
	bool isFrame;		// ������ �̹�����
	int frameX, frameY; // ������ X,Y
	int value;			// �󸶳�

};

struct tagItem // ������
{
	image* image[3];			// 0.��� 1.�κ� 2. ����
	RECT rc[3];					// ��Ʈ
	ITEMTYPE type;				// ������ ����
	ITEMGRADE grade;			// ������ ���
	DROPITEM drop;				// ��������� �϶�
	INVENITEM inven;			// �κ������� �϶�
	WEARITEM wear;				// ��������� �϶�
	float x, y;					//x, y ��ǥ
	bool isFrame;				// ������ �̹��� ���� �ƴ��� Ȯ��
	bool sellBan;				// ������ �Ǹű��� ��ų��
	int frameX, frameY;			//������ X, Y
	int minimumAtt, MaxAtt;		//�ּ� ~ �ִ� ���ݷ� 20 ~ 30 �̸� �������� 22����?
	int fixedDamage;			//������ 22;
	int ad;						//���ݷ� ����
	int def;					//���� ����					
	float attackSpeed;			//���ݼӵ� 
	float moveMentSpeed;		//�̵��ӵ� 
	float criticalPersent;		//ũ��Ƽ��Ȯ�� ����
	float evasionPersent;		//ȸ���� 
	float hpRecovery;			//hpȸ�� 
	float dashPower;			//��ð��ݷ� ������ 
	int addMaxHp;				//�ִ� HP ����
	int price;					//���� 
	const char* name;			// �̸�
	int value;					// ���ڹޱ����ؾ�

};

class Item : public gameNode
{
private:

	tagItem _item;
	int _count;
	
	
public:
	Item();
	~Item();

	HRESULT init(ITEMTYPE type, const char* itemName, int value, POINT position);
	void release();
	void update();
	void render();


	void CreateItem(ITEMTYPE type, const char* itemName, int value); // ������ �������
	void setSword(const char* weaponName, int value);			// �� ��������
	void setHammer(const char * weaponName, int value);			// �ظ� ��������
	void setGun(const char * weaponName, int value);			// �� ��������
	void setBow(const char * weaponName, int value);			// Ȱ ��������
	void setArmor(const char* ArmorName, int value);			// �Ƹ� ��������
	void setShield(const char* ShieldName, int value);			// ���� ��������
	void setEquip(const char* secondEquipment, int value);		// ������� ��������
	void setAccessory(const char* AccessoryName, int value);	// �Ǽ� ��������
	void setFood(const char* FoodName, int value);				// ���� ��������

	tagItem getItem() { return _item; }
	
	//void dropItem(DROPITEM type, const char* dropItem, int value);			// ��� ������ �������
	//void setDropItem(const char* dropItem, int value);						// ��������� ��������


	//void invenItem(INVENITEM type, const char* invenItem, int value);		// �κ������� �������							
	//void setInvenItem(const char* invenItem, int value);					// �κ��丮�� ���⸦ �����ϰ� ���� �� or �κ��丮 �ȿ��� ���� �ϰ� ���� ��


	//void wearItem();				// ��������� �������
	//void wearWeapon();				// ���⸦ �����ϰ� ������
	//void wearsecond();				// ������� �����ϰ� ���� ��

	//void storeItem();				// ���� ������ �������~~
	//void setIfStoreItemIsWeapon();	// �������� �Ȱ� �ִ� �������� ������ ��
	//void setIfStoreItemIsDefence();	// �������� �Ȱ� �ִ� �������� �� �� ��
	//void setIfStoreItemIsFood();	// �������� �Ȱ� �ִ� �������� ������ ��



};
