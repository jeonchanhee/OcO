#include "stdafx.h"
#include "Food.h"


Food::Food(){} Food::~Food(){}

HRESULT Food::init(ITEMTYPE type, const char * FoodName, int value, POINT position)
{
	_food.type = type;
	_foodName = FoodName;
	_value = value;
	_food.x = position.x;
	_food.y = position.y;

	CreateFood(type, FoodName, value);

	return S_OK;
}

void Food::release()
{
}

void Food::update()
{

}

void Food::CreateFood(ITEMTYPE type, const char * FoodName, int value)
{
	switch (type)
	{
		case FOOD:
			setFood(FoodName, value);
		break;
	}
}

void Food::setFood(const char * FoodName, int value)
{
	char str[128];
	for (int i = 1; i < 13; i++)
	{
		sprintf_s(str, "%s%d", FoodName, value);
		_food.image[i] = IMAGEMANAGER->findImage(str);
		_food.rc[i] = RectMake(_food.x + 1 * i, _food.y, _food.image[i]->getWidth(),
			_food.image[i]->getHeight());
	}
	
	if (value == 1)
	{
		_food.addMaxHp = 4;				// �ִ�ü�� ����
		_food.hpRecovery = 4.0f;		// ü��ȸ��
		_food.ad = 4.0f;				// ���ݷ� ����.
		_food.attackSpeed = 4.0f;		// ��������
		_food.price = 250;				// ���� ����
	}

	if (value == 2)
	{
		_food.addMaxHp = 5;				// �ִ�ü�� ����
		_food.hpRecovery = 5.0f;		// ü��ȸ��
		_food.criticalPersent = 5.0f;	// ũ���� ����
		_food.evasionPersent = 5.0f;	// ȸ���� ����
		_food.price = 300;				// ���� ����
	}
	
	if (value == 3)
	{
		_food.addMaxHp = 6;				// �ִ�ü�� ����
		_food.hpRecovery = 6.0f;		// ü��ȸ��
		_food.attackSpeed = 6.0f;		// ��������
		_food.moveMentSpeed = 6.0f;		// �̵��ӵ� ����
		_food.price = 350;				// ���� ����
	}

	if (value == 4)
	{
		_food.addMaxHp = 7;				// �ִ�ü�� ����
		_food.hpRecovery = 7.0f;		// ü��ȸ��
		_food.evasionPersent = 7.0f;	// ȸ���� ����
		_food.moveMentSpeed = 7.0f;		// �̵��ӵ� ����
		_food.price = 400;				// ���� ����
	}
	if (value == 5)
	{
		_food.addMaxHp = 8;				// �ִ�ü�� ����
		_food.hpRecovery = 8.0f;		// ü��ȸ��
		_food.ad = 8.0f;				// ���ݷ� ����.
		_food.attackSpeed = 8.0f;		// ��������
		_food.criticalPersent = 8.0f;	// ũ���� ����
		_food.price = 450;				// ���� ����
	}
	if (value == 6)
	{
		_food.addMaxHp = 9;				// �ִ�ü�� ����
		_food.hpRecovery = 9.0f;		// ü��ȸ��
		_food.ad = 9.0f;				// ���ݷ� ����.
		_food.attackSpeed = 9.0f;		// ��������
		_food.evasionPersent = 9.0f;	// ȸ���� ����
		_food.price = 500;				// ���� ����
	}
	if (value == 7)
	{
		_food.addMaxHp = 10;			// �ִ�ü�� ����
		_food.hpRecovery = 10.0f;		// ü��ȸ��
		_food.ad = 10.0f;				// ���ݷ� ����.
		_food.attackSpeed = 10.0f;		// ��������
		_food.moveMentSpeed = 10.0f;	// �̵��ӵ� ����
		_food.price = 550;				// ���� ����
	}
	if (value == 8)
	{
		_food.addMaxHp = 10;			// �ִ�ü�� ����
		_food.hpRecovery = 14.0f;		// ü��ȸ��
		_food.ad = 10.0f;				// ���ݷ� ����.
		_food.attackSpeed = 10.0f;		// ��������
		_food.price = 600;				// ���� ����
	}
	if (value == 9)
	{
		_food.addMaxHp = 10;			// �ִ�ü�� ����
		_food.hpRecovery = 10.0f;		// ü��ȸ��
		_food.criticalPersent = 20.0f;	// ũ���� ����
		_food.evasionPersent = 20.0f;	// ȸ���� ����
		_food.moveMentSpeed = 20.0f;	// �̵��ӵ� ����
		_food.price = 650;				// ���� ����
	}
	if (value == 10)
	{
		_food.addMaxHp = 10;			// �ִ�ü�� ����
		_food.hpRecovery = 10.0f;		// ü��ȸ��
		_food.ad = 5.0f;				// ���ݷ� ����.
		_food.attackSpeed = 5.0f;		// ��������
		_food.criticalPersent = 5.0f;	// ũ���� ����
		_food.evasionPersent = 5.0f;	// ȸ���� ����
		_food.moveMentSpeed = 5.0f;		// �̵��ӵ� ����
		_food.price = 700;				// ���� ����
	}
	if (value == 11)
	{
		_food.addMaxHp = 10;			// �ִ�ü�� ����
		_food.hpRecovery = 10.0f;		// ü��ȸ��
		_food.ad = 5.0f;				// ���ݷ� ����.
		_food.attackSpeed = 5.0f;		// ��������
		_food.criticalPersent = 5.0f;	// ũ���� ����
		_food.evasionPersent = 5.0f;	// ȸ���� ����
		_food.moveMentSpeed = 5.0f;		// �̵��ӵ� ����
		_food.price = 750;				// ���� ����
	}
	if (value == 12)
	{
		_food.addMaxHp = 10;			// �ִ�ü�� ����
		_food.hpRecovery = 10.0f;		// ü��ȸ��
		_food.ad = 5.0f;				// ���ݷ� ����.
		_food.attackSpeed = 5.0f;		// ��������
		_food.criticalPersent = 5.0f;	// ũ���� ����
		_food.evasionPersent = 5.0f;	// ȸ���� ����
		_food.moveMentSpeed = 5.0f;		// �̵��ӵ� ����
		_food.price = 800;				// ���� ����
	}


}

void Food::render()
{
	for (int i = 0; i < 12; i++)
	{
		_food.image[i]->render(DC, _food.rc[i].left, _food.rc[i].top);
	}
}