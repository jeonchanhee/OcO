#include "stdafx.h"
#include "Armor.h"


Armor::Armor(){} Armor::~Armor(){}

HRESULT Armor::init(ITEMTYPE type, const char* armorName, int value, POINT position)
{
	_armor.type = type;
	_armorName = armorName;
	_value = value;
	_armor.x = position.x;
	_armor.y = position.y;

	CreateArmor(type, armorName, value);
	

	return S_OK;
}

void Armor::release()
{
}

void Armor::update()
{

}


void Armor::CreateArmor(ITEMTYPE type, const char* ArmorName, int value)
{

	switch (type)
	{
	case ARMOR:
		setArmor(ArmorName, value);
		break;
	}

	
}

void Armor::setArmor(const char* ArmorName, int value)
{
	char str[128];
	for (int i = 0; i < 2; i++)
	{
		sprintf_s(str, "%s%d%d", ArmorName, value, i);
		_armor.image[i] = IMAGEMANAGER->findImage(str);
		_armor.rc[i] = RectMakeCenter(_armor.x + i * 100, _armor.y, _armor.image[i]->getWidth(),
		_armor.image[i]->getHeight());
	}

	if (value == 1) //��� ����
	{
		_armor.grade = NORMAL;				// ������ ���
		_armor.def = 3;						// ����
		_armor.price = 700;					// ����

	}

	if (value == 2) // ���װ���
	{
		_armor.grade = NORMAL;				// ������ ���
		_armor.def = 5;						// ����
		_armor.price = 900;					// ����
	}

	if (value == 3) // �Ұ��� ����
	{
		_armor.grade = NORMAL;				// ������ ���
		_armor.def = 8;						// ����
		_armor.price = 1200;				// ����
	}

	if (value == 4) // ü�ξƸ�
	{
		_armor.grade = NORMAL;				// ������ ���
		_armor.def = 12;					// ����
		_armor.price = 1500;				// ����
	}

}

void Armor::render()
{
	for (int i = 0; i < 2; i++)
	{
		_armor.image[i]->render(DC, _armor.rc[i].left, _armor.rc[i].top);
	}
}
