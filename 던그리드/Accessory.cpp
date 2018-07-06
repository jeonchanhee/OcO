#include "stdafx.h"
#include "Accessory.h"


Accessory::Accessory(){} Accessory::~Accessory(){}

HRESULT Accessory::init(ITEMTYPE type, const char* AccessoryName, int value, POINT position)
{
	_accessory.type = type;
	_AccessoryName = AccessoryName;
	_value = value;
	_accessory.x = position.x;
	_accessory.y = position.y;

	CreateAccessory(type, AccessoryName, value);
	return S_OK;
}

void Accessory::release()
{
}

void Accessory::update()
{
}

void Accessory::CreateAccessory(ITEMTYPE type, const char* AccessoryName, int value)
{
	switch (type)
	{
	case ACCESSORY:
		setAccessory(AccessoryName, value);
		break;
	}

}

void Accessory::setAccessory(const char* AccessoryName, int value)
{
	char str[128];
	for (int i = 0; i < 2; i++)
	{
		sprintf_s(str, "%s%d%d", AccessoryName, value, i);
		_accessory.image[i] = IMAGEMANAGER->findImage(str);
		_accessory.rc[i] = RectMakeCenter(_accessory.x + i * 100, _accessory.y, _accessory.image[i]->getWidth(),
			_accessory.image[i]->getHeight());
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

void Accessory::render()
{
	for (int i = 0; i < 2; i++)
	{
		_accessory.image[i]->render(DC, _accessory.rc[i].left, _accessory.rc[i].top);
	}
}