#pragma once
#include "Item.h"



struct tagWeapon // ���� ����ü~~
{
	image* image[3];			// 0.��� 1.�κ� 2. ����
	RECT rc[3];					// ��Ʈ
	ITEMTYPE type;				// ������ ����
	ITEMGRADE grade;			// ������ ���
	float x, y;					//x, y ��ǥ
	bool isFrame;				// ������ �̹��� ���� �ƴ��� Ȯ��
	bool sellBan;				// �Ǹű��� ������ ���� �ƴ���
	int frameX, frameY;			//������ X, Y
	int minimumAtt, MaxAtt;		//�ּ� ~ �ִ� ���ݷ� 20 ~ 30 �̸� �������� 22����?
	int fixedDamage;			//������ 22;
	float attackSpeed;			//���ݼӵ�	
	float moveMentSpeed;		//�̵��ӵ�
	float criticalPersent;		//ũ��Ƽ��Ȯ��
	float evasionPersent;		//ȸ����
	float dashPower;			//��ð��ݷ� ������ 
	int addMaxHp;				//�ִ� HP ����
	int price;					//���� ?? �������� �춧 3õ���̶���ϸ� �ȶ��� X 0.2 �ؼ� 600 �̷������� ����å��
};


class Weapon :	public Item
{
private:

	tagWeapon _weapon;
	int _count;

	const char* _weaponName;
	int _value;
	
public:
	Weapon();
	~Weapon();

	HRESULT init(ITEMTYPE type, const char* weaponName, int value, POINT position);
	void release();
	void update();
	void render();

	void CreateWeapon(ITEMTYPE type, const char* weaponName, int value);
	void setSword(const char* weaponName, int value);
	void setHammer(const char * weaponName, int value);
	void setGun(const char * weaponName, int value);
	void setBow(const char * weaponName, int value);



};

