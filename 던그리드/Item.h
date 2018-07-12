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
	const char* name;			// �̸�
	image* image[3];			// 0.��� 1.�κ� 2. ����
	RECT rc[3];					// ��Ʈ
	ITEMTYPE type;				// ������ ����
	ITEMGRADE grade;			// ������ ���
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

	HRESULT init(ITEMTYPE type, const char * itemName, int value, POINT position);
	void release();
	void update();
	void render();
	void invenRender(HDC hdc, int x, int y);


	void CreateItem(ITEMTYPE type, const char* itemName, int value); // ������ ���巯��
	
	void setSword(const char* weaponName, int value);				// �� ��������
	void setHammer(const char * weaponName, int value);				// �ظ� ��������
	void setGun(const char * weaponName, int value);				// �� ��������
	void setBow(const char * weaponName, int value);				// Ȱ ��������
	void setArmor(const char* ArmorName, int value);				// �Ƹ� ��������
	void setShield(const char* ShieldName, int value);				// ���� ��������
	void setEquip(const char* secondEquipment, int value);			// ������� ��������
	void setAccessory(const char* AccessoryName, int value);		// �Ǽ� ��������
	void setFood(const char* FoodName, int value);					// ���� ��������

	ITEMTYPE getItemType() { return _item.type; }
	image * equipmentImage() { return _item.image[2]; }
	tagItem getItem() { return _item; }
	



};
