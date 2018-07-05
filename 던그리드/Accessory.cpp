#include "stdafx.h"
#include "Accessory.h"


Accessory::Accessory(){} Accessory::~Accessory(){}

HRESULT Accessory::init(POINT position)
{
	_accessory.x = position.x;
	_accessory.y = position.y;
	for (int i = 0; i < 3; i++)
	{
		_accessory.rc[i] = RectMakeCenter(_accessory.x, _accessory.y, _accessory.image[i]->getWidth(),
			_accessory.image[i]->getHeight());
	}

	return S_OK;
}

void Accessory::release()
{
}

void Accessory::update()
{
}

void Accessory::render()
{
	for (int i = 0; i < 3; i++)
	{
		_accessory.image[i]->render(DC, _accessory.rc[i].left, _accessory.rc[i].top);
	}
}

void Accessory::CreateAccessory(ITEMTYPE type, const char* ArmorName, int value, POINT position)
{
	switch (type)
	{
	case ARMOR:
		setAccessory(ArmorName, value);
		break;
	}

}

void Accessory::setAccessory(const char* ArmorName, int value)
{
	char str[128];
	for (int i = 0; i < 3; i++)
	{
		sprintf_s(str, "%s%d%d", ArmorName, value, i);
		_accessory.image[i] = IMAGEMANAGER->findImage(str);
	}

	if (value == 1) // ���彺�渵
	{
		_accessory.grade = NORMAL;				// ������ ���
		_accessory.def = 3;						// ����
		_accessory.addMaxHp = 5;				// ü��	
		_accessory.price = 1500;				// ����

	}

	if (value == 2) // �ƹķ�
	{
		_accessory.grade = RARE;				// ������ ���
		_accessory.attackSpeed = 5.0f;			// ����
		_accessory.evasionPersent = 8.0f;		// ȸ���� 
		_accessory.price = 3000;				// ����
	}

	if (value == 3) // ���ν�Ʈ �����
	{
		_accessory.grade = RARE;				// ������ ���
		_accessory.attackSpeed = 5.0f;			// ����
		_accessory.criticalPersent = 8.0f;		// ũ����
		_accessory.price = 3000;				// ����
	}

	if (value == 4) // �Ը����� ��
	{
		_accessory.grade = RARE;				// ������ ���
		_accessory.def = 6;						// ����
		_accessory.addMaxHp = 10;				// hp����
		_accessory.price = 3000;				// ����
	}

}
