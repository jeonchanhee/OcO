#include "stdafx.h"
#include "Shield.h"


Shield::Shield(){} Shield::~Shield(){}

HRESULT Shield::init(ITEMTYPE type, const char* ShieldName, int value, POINT position)
{
	_shield.type = type;
	_ShieldName = ShieldName;
	_value = value;
	_shield.x = position.x;
	_shield.y = position.y;

	CreateShield(type, ShieldName, value);
	return S_OK;
}

void Shield::release()
{
}

void Shield::update()
{

}

void Shield::CreateShield(ITEMTYPE type, const char * ShieldName, int value)
{



	switch (type)
	{
	case SHIELD:
		setShield(ShieldName, value);
		break;
	}
}

void Shield::setShield(const char * ShieldName, int value)
{
	char str[128];
	for (int i = 0; i < 3; i++)
	{
		sprintf_s(str, "%s%d%d", ShieldName, value, i);
		_shield.image[i] = IMAGEMANAGER->findImage(str);
		_shield.rc[i] = RectMake(_shield.x + i * 100, _shield.y + i * 100, _shield.image[i]->getWidth(),
			_shield.image[i]->getHeight());
		
	}

	if (value == 1)
	{
		_shield.grade = NORMAL;	// ���� ���
		_shield.def = 10;		// ����
		_shield.price = 1500;	// ����
	}

	if (value == 2)
	{
		_shield.grade = RARE;			// ���� ���
		_shield.def = 30;				// ����
		_shield.addMaxHp = 100;			// ü������
		_shield.evasionPersent = 10.0f; // ȸ����
		_shield.dashPower = 50.0f;		// �뽬���� ����
	}

	
}


void Shield::render()
{
	for (int i = 0; i < 3; i++)
	{
		_shield.image[i]->render(DC, _shield.rc[i].left, _shield.rc[i].top);
	}

}




